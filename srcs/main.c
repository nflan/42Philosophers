/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:07:53 by nflan             #+#    #+#             */
/*   Updated: 2022/04/12 18:24:19 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

pthread_mutex_t	lock;

void	ft_print_all(t_all *g)
{
	//	t_phil	*tmp;

	//	tmp = g->p;
	printf("tdie = %lld\n", g->tdie);
	printf("teat = %lld\n", g->teat);
	printf("tsleep = %lld\n", g->tsleep);
	//	printf("Philosophers :\n");
	//	while (tmp)
	//	{
	//		printf("%d fait %d\n", tmp->i, tmp->act);
	//		tmp = tmp->next;
	//	}
}

int	ft_free_all(char *str, t_all *g, int code)
{
/*	int	i;

	i = 0;
	ft_putstr_fd(str, 2);
	if (g)
	{
		if (g->tv)
			free(g->tv);
		free(g);
		g = NULL;
	}
*/	(void)str;
	(void)g;
	return (code);
}

int	ft_init_mutex(t_all *g)
{
	int	i;

	i = g->nbphilo;
	while (i-- > 0)
	{
		if (pthread_mutex_init(&g->forks[i], NULL))
			return (1);
	}
	if (pthread_mutex_init(&g->lock, NULL))
		return (1);
	if (pthread_mutex_init(&g->meal_check, NULL))
		return (1);
	return (0);
}

int	ft_init_philo(t_all *g)
{
	int	i;

	i = 0;
	while (i < g->nbphilo)
	{
		g->philo[i].id = i + 1;
		g->philo[i].x_ate = 0;
		g->philo[i].left_fork_id = i;
		g->philo[i].right_fork_id = (i + 1) % g->nbphilo;
		g->philo[i].last_meal = 0;
		g->philo[i].g = g;
		i++;
	}
	return (0);
}

int	ft_init_all(t_all *g, char **av)
{
	pthread_mutex_t	forks[ft_atoi(av[1])];
	t_phil			philo[ft_atoi(av[1])];

	g->nbphilo = ft_atoi(av[1]);
	g->tdie = ft_atoi(av[2]);
	g->teat = ft_atoi(av[3]);
	g->tsleep = ft_atoi(av[4]);
	g->died = 0;
	g->all_ate = 0;
	if (av[5])
	{
		g->nbeat = ft_atoi(av[5]);
		if (g->nbeat <= 0)
			return (1);
	}
	else
		g->nbeat = -1;
	g->forks = forks;
	if (ft_init_mutex(g))
		return (1);
	g->philo = philo;
	ft_init_philo(g);
	return (0);
}

long long	ft_get_time(void)
{
	struct timeval	*tv;
	long long		time;

	tv = NULL;
	time = 0;
	tv = ft_calloc(sizeof(struct timeval), 1);
	if (!tv)
		return (-1);
	if (gettimeofday(tv, tv) == -1)
		return (-1);
	time = tv->tv_usec;
	free(tv);
	return (time);
}

//valgrind --tool=helgrind ./philo pour voir les acces concurrents

void	ft_action_print(t_all *g, int id, char *str)
{
	long long	time;

	time = ft_get_time();
	time -= g->first_timeval;
	printf("%lld %d %s\n", time, id, str);
}

void	ft_sleep(t_all *g)
{
	usleep(g->tsleep);
}

void	ft_philo_eats(t_all *g, t_phil *phil)
{
	pthread_mutex_lock(&g->forks[phil->left_fork_id]);
	ft_action_print(g, phil->id, "has taken a fork");
	pthread_mutex_lock(&g->forks[phil->right_fork_id]);
	ft_action_print(g, phil->id, "has taken a fork");
	ft_action_print(g, phil->id, "is eating");
	usleep(g->teat);
	pthread_mutex_unlock(&g->forks[phil->right_fork_id]);
	pthread_mutex_unlock(&g->forks[phil->left_fork_id]);
}

void	*ft_thread(void *arg)
{
	//	char	*msg;
	t_phil		*phil;
	t_all		*g;
	int			i;

	i = 0;
	phil = (t_phil *) arg;
	g = phil->g;
	if (phil->id % 2)
		usleep(g->teat);
	while (!g->died)
	{
		ft_philo_eats(g, phil);
		if (g->all_ate)
			break;
		ft_action_print(g, phil->id, "is sleeping");
		ft_sleep(g);
		ft_action_print(g, phil->id, "is thinking");
	}
	return (NULL);
}	
/*	pthread_mutex_init(&phil->left_fork_id, NULL);
	pthread_mutex_init(&g->forks[1], NULL);

	g->philo->id++;
	printf("g->philo->id = %d\n", g->philo->id);
	time = ft_get_time(g, 0);
	while (time > 1 && time < g->tdie)
	{
		pthread_mutex_lock(&g->forks[0]);
		pthread_mutex_lock(&g->forks[1]);
		ft_get_time(g, 1);
		time = ft_get_time(g, 0);
		if (time <= 1 && time > g->tdie)
		{
			pthread_mutex_unlock(&g->forks[0]);
			pthread_mutex_unlock(&g->forks[1]);
			ft_get_time(g, 5);
			return (NULL);
		}
		ft_get_time(g, 1);
		ft_get_time(g, 2);
		time = ft_get_time(g, 0);
		if (time <= 1 && time > g->tdie - g->teat)
		{
			pthread_mutex_unlock(&g->forks[0]);
			pthread_mutex_unlock(&g->forks[1]);
			ft_get_time(g, 5);
			return (NULL);
		}
		usleep(g->teat);
		time = ft_get_time(g, 0);
		if (time <= 1)
		{
			pthread_mutex_unlock(&g->forks[0]);
			pthread_mutex_unlock(&g->forks[1]);
			ft_get_time(g, 5);
			return (NULL);
		}
		g->tdie = g->tdie + ft_get_time(g, 0);
	//	printf("g->tdie = %lld\n", g->tdie);
		pthread_mutex_unlock(&g->forks[0]);
		pthread_mutex_unlock(&g->forks[1]);
		ft_get_time(g, 3);
		usleep(g->tsleep);
		time = ft_get_time(g, 0);
	//	printf("time = %lld\n", time);
	}
	ft_get_time(g, 5);
//	printf("g->tdie = %lld\n", g->tdie);
	return (NULL);
}*/

int	ft_end_philo(t_all *g, t_phil *phil)
{
	int	i;

	i = 0;
	while (i++ < g->nbphilo)
		pthread_join(phil[i].thread_id, NULL);
	i = 0;
	while (i++ < g->nbphilo)
		pthread_mutex_destroy(&g->forks[i]);
	pthread_mutex_destroy(&g->lock);
	return (0);
}

int	ft_check_death(t_all *g, t_phil *phil)
{
	if (phil->last_meal + g->tsleep > phil->last_meal + g->tdie)
	{
		g->died = 1;
		ft_action_print(g, phil->id, "died");
		return (1);
	}
	return (0);
}

int	ft_philosophers(t_all *g)
{
	t_phil	*phil;
	int		i;

	i = 0;
	phil = g->philo;
	g->first_timeval = ft_get_time();
	if (g->first_timeval <= 0)
		return (ft_free_all("Get time error\n", g, 1));
	while (i < g->nbphilo)
	{
		if (pthread_create(&phil[i].thread_id, NULL, ft_thread, &phil[i]))
			return (1);
		phil[i].last_meal = ft_get_time();
		i++;
	}
	i = 0;
	ft_check_death(g, phil);
	ft_end_philo(g, phil);
	//ft_free_all("", g, 0);
	return (0);
}

int	main(int ac, char **av)
{
	//	char		*msg1 = "First Thread";
	t_all		g;

	if (ft_parsing(ac, av, 0))
		return (ft_free_all("Parsing error\n", &g, 1));
	if (ft_init_all(&g, av))
		return (ft_free_all("Init error\n", &g, 1));
	if (ft_philosophers(&g))
		return (ft_free_all("Threads init error\n", &g, 1));
	return (0);
}
