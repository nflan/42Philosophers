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

long long	ft_time_check(long long past, long long now)
{
	return (now - past);
}

void	ft_usleep(long long time, t_all *g)
{
	long long i;

	i = ft_get_time();
	while (!g->died)
	{
		if (ft_time_check(i, ft_get_time()) >= time)
			break ;
		usleep(50);
	}
}

void	ft_action_print(t_all *g, int id, char *str)
{
	long long	time;

	pthread_mutex_lock(&g->lock);
	time = ft_get_time();
	time -= g->first_timeval;
	printf("%lld %d %s\n", time, id, str);
	pthread_mutex_unlock(&g->lock);
}

void	ft_death_checker(t_all *g, t_phil *phil)
{
	int i;

	while (!g->all_ate)
	{
		i = -1;
		while (++i < g->nbphilo && !g->died)
		{
			pthread_mutex_lock(&g->meal_check);
			if (ft_time_check(phil[i].last_meal, ft_get_time()) > g->tdie)
			{
				ft_action_print(g, i, "died");
				g->died = 1;
			}
			pthread_mutex_unlock(&g->meal_check);
			usleep(100);
		}
		if (g->died)
			break ;
		i = 0;
		while (g->nbeat != -1 && i < g->nbphilo && phil[i].x_ate >= g->nbeat)
			i++;
		if (i == g->nbphilo)
			g->all_ate = 1;
	}
}

long long	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_usec);
}

//valgrind --tool=helgrind ./philo pour voir les acces concurrents

void	ft_philo_eats(t_all *g, t_phil *phil)
{
	pthread_mutex_lock(&g->forks[phil->left_fork_id]);
	ft_action_print(g, phil->id, "has taken a fork");
	pthread_mutex_lock(&g->forks[phil->right_fork_id]);
	ft_action_print(g, phil->id, "has taken a fork");
	pthread_mutex_lock(&g->meal_check);
	ft_action_print(g, phil->id, "is eating");
	phil->last_meal = ft_get_time();
	pthread_mutex_unlock(&g->meal_check);
	ft_usleep(g->teat, g);
	phil->x_ate++;
	pthread_mutex_unlock(&g->forks[phil->left_fork_id]);
	pthread_mutex_unlock(&g->forks[phil->right_fork_id]);
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
		ft_usleep(g->tsleep, g);
		ft_action_print(g, phil->id, "is thinking");
		i++;
	}
	return (NULL);
}

int	ft_end_philo(t_all *g, t_phil *phil)
{
	int	i;

	i = -1;
	while (++i < g->nbphilo)
		pthread_join(phil[i].thread_id, NULL);
	i = -1;
	while (++i < g->nbphilo)
		pthread_mutex_destroy(&g->forks[i]);
	pthread_mutex_destroy(&g->lock);
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
	ft_death_checker(g, phil);
	ft_end_philo(g, phil);
	return (0);
}

int	main(int ac, char **av)
{
	t_all		g;

	if (ft_parsing(ac, av, 0))
		return (ft_free_all("Parsing error\n", &g, 1));
	if (ft_init_all(&g, av))
		return (ft_free_all("Init error\n", &g, 1));
	if (ft_philosophers(&g))
		return (ft_free_all("Threads init error\n", &g, 1));
	return (0);
}
