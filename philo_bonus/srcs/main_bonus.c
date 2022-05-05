/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:06:37 by nflan             #+#    #+#             */
/*   Updated: 2022/05/05 15:01:31 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	ft_print_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	ft_init_philo(t_all *g)
{
	int	i;
	
	i = g->nbphilo;
	while (--i >= 0)
	{
		g->philo[i].id = i;
		g->philo[i].g = g;
		g->philo[i].last_meal = 0;
	}
	return (0);
}

int	ft_init_sem(t_all *g)
{
	g->sem = "FORKS";
	g->sem_d = "DEATH";
	g->sem_p = "PRINT";
	g->sem_die = "DIE";
	g->sem_t = "TIME";
	sem_unlink(g->sem);
	sem_unlink(g->sem_d);
	sem_unlink(g->sem_p);
	sem_unlink(g->sem_die);
	g->forks = sem_open(g->sem, O_CREAT, 0660, g->nbphilo);
	g->death = sem_open(g->sem_d, O_CREAT, 0660, 1);
	g->print = sem_open(g->sem_p, O_CREAT, 0660,1);
	g->die = sem_open(g->sem_die, O_CREAT, 0660,1);
	sem_unlink(g->sem_t);
	g->time = sem_open(g->sem_t, O_CREAT, 0660, g->nbphilo);
	if (g->time == SEM_FAILED)
		return (ft_print_error("Sem open failed"));
	if (g->forks == SEM_FAILED || g->death == SEM_FAILED || g->print == SEM_FAILED || g->die == SEM_FAILED)
		return (ft_print_error("Sem open failed"));
	return (0);
}

int	ft_init_all(t_all *g, char **av)
{
	g->nbphilo = ft_atoi(av[1]);
	g->tdie = ft_atoi(av[2]);
	g->teat = ft_atoi(av[3]);
	g->tsleep = ft_atoi(av[4]);
	g->eat_count = 0;
	g->died = 0;
	if (av[5] && ft_atoi(av[5]) >= 0)
	{
		if (ft_atoi(av[5]) == 0)
			return (2);
		g->nbeat = ft_atoi(av[5]) + 1;
		g->sem_e = "EAT";
		sem_unlink(g->sem_e);
		g->eat = sem_open(g->sem_e, O_CREAT, 0660, 1);
		if (g->eat == SEM_FAILED)
			return (ft_print_error("Sem open failed"));
	}
	else
		g->nbeat = -1;
	if (ft_init_sem(g))
		return (1);
	ft_init_philo(g);
	return (0);
}

void	ft_philo_eats(t_all *g, t_phil *phil)
{
	sem_wait(g->forks);
	ft_action_print(g, phil->id, "has taken a fork\n");
	sem_wait(g->forks);
	ft_action_print(g, phil->id, "has taken a fork\n");
	ft_action_print(g, phil->id, "is eating\n");
//	sem_wait(g->eat);
	if (g->nbeat != -1)
	{
	//	sem_wait(g->eat);
		g->eat_count++;
	//	sem_post(g->eat);
	}
//	sem_wait(g->die);
	phil->last_meal = ft_get_time();
//	sem_post(g->die);
//	printf("last meal = %lld && id = %d\n", ft_time_check(g->first_timeval, phil->last_meal), phil->id + 1);
//	sem_post(g->eat);
	ft_usleep(g->teat, g);
	sem_post(g->forks);
	sem_post(g->forks);
}

void	*ft_thread(t_all *g, t_phil phil)
{
	if (pthread_create(&phil.thread_id, NULL, ft_death_checker, &phil))
		return (ft_end_philo(g, 1));
	pthread_detach(phil.thread_id);
	if (phil.id % 2)
		ft_usleep(g->teat / 2, g);
	while (1)
	{
		ft_philo_eats(g, &phil);
//		sem_wait(g->die);
//		if (g->died)
//			break ;
//		sem_post(g->die);
		ft_action_print(g, phil.id, "is sleeping\n");
		ft_usleep(g->tsleep, g);
		ft_action_print(g, phil.id, "is thinking\n");
	}
//	pthread_join(phil.thread_id, NULL);
//	return (ft_end_philo(g, 0));
	return (NULL);
}

/*void	ft_philo_eats(t_all *g, t_phil *phil)
{
//	sem_wait(g->print);
//	write(1, "forks = ", 6);
//	ft_putnbr(g->forks->__align);
//	write(1, "\n", 1);
//	sem_post(g->print);
	sem_wait(g->forks);
	ft_action_print(g, phil->id, "has taken a fork\n");
	sem_wait(g->forks);
	ft_action_print(g, phil->id, "has taken a fork\n");
	ft_action_print(g, phil->id, "is eating\n");
	sem_wait(g->die);
	phil->last_meal = ft_get_time();
	sem_post(g->die);
	if (g->nbeat != -1)
		g->eat_count++;
	ft_usleep(g->teat, g);
	sem_post(g->forks);
	sem_post(g->forks);
//	{
//		write(1, "allo\n", 5);
//	}
}

void	*ft_philo_t(void *arg)
{
	t_phil	*phil;
	t_all	*g;

	phil = (t_phil *)arg;
	g = phil->g;
	ft_action_print(g, phil->id, "is thinking\n");
	while (!g->died)
	{
		ft_philo_eats(g, phil);
		sem_wait(g->die);
		if (g->died)
			break ;
		sem_post(g->die);
		ft_action_print(g, phil->id, "is sleeping\n");
		ft_usleep(g->tsleep, g);
		ft_action_print(g, phil->id, "is thinking\n");
	}
	return (NULL);
}

void	*ft_thread(t_all *g, t_phil phil)
{
//	if (pthread_create(&phil.thread_id, NULL, ft_death_checker, &phil))
//		return (ft_end_philo(g, 1));
	if (phil.id % 2)
		usleep(g->teat * 800);
	if (pthread_create(&phil.philo_id, NULL, ft_philo_t, &phil))
		return (ft_end_philo(g, 1));
	if (pthread_create(&phil.thread_id, NULL, ft_death_checker, &phil))
		return (ft_end_philo(g, 1));
	sem_wait(g->death);
	printf("g->die = %ld\n", g->die->__align);
	printf("g->death = %ld\n", g->death->__align);
	printf("g->print = %ld\n", g->print->__align);
	printf("g->eat = %ld\n", g->eat->__align);
	printf("g->forks = %ld\n", g->forks->__align);
//	pthread_join(phil.philo_id, NULL);
//	pthread_detach(phil.thread_id);
	return (ft_end_philo(g, 0));
}*/

/*int	ft_philosophers(t_all *g)
{
//	t_phil	*phil;
	int		i;

	i = -2;
	g->first_timeval = ft_get_time();
	sem_wait(g->death);
	while (i < g->nbphilo)
	{
		i += 2;
		if (i < g->nbphilo)
		{
			g->philo[i].child = fork();
			if ((int) g->philo[i].child == -1)
				return (ft_print_error("Child error"));
			else if ((int) g->philo[i].child == 0)
			{
				if (ft_thread(g, g->philo[i]))
					return (1);
				g->philo[i].last_meal = ft_get_time();
			}
		}
		if (g->nbphilo % 2 && i == g->nbphilo - 1)
			i = -1;
		else if (g->nbphilo % 2 == 0 && i == g->nbphilo)
			i = -1;
	}
	i = -1;
	sem_wait(g->death);
	while (++i < g->nbphilo)
		kill(g->philo[i].child, SIGKILL);
//		waitpid(g->philo[i].child, &g->philo[i].child, 0);
	ft_end_philo(g, 0);
	return (0);
}*/

void	*ft_launch(void *arg)
{
	int		i;
	int		end;
	t_all	*g;

	g = (t_all *) arg;
	i = g->in_i;
	end = g->in_end;
	while (i < end)
	{
		g->philo[i].child = fork();
		if ((int) g->philo[i].child == -1)
			return (NULL);
		else if ((int) g->philo[i].child == 0)
		{
			g->philo[i].last_meal = ft_get_time();
			if (ft_thread(g, g->philo[i]))
				return (NULL);
		}
		i++;
	}
	return (NULL);
}

int	ft_philosophers(t_all *g)
{
	int			i;
	pthread_t	thread[4];

	i = 0;
	g->in_i = 0;
	g->in_end = g->nbphilo / 4;
	g->first_timeval = ft_get_time();
	sem_wait(g->death);
	while (i < 4)
	{
		if (pthread_create(&thread[i], NULL, ft_launch, &g))
			return (1);
		g->in_i += g->in_end;
		g->in_end += g->in_end;
		if (i == 2)
			g->in_end = g->nbphilo;
//		i += g->nbphilo / 4;
		i++;
	}
	i = -1;
	sem_wait(g->death);
	while (++i < g->nbphilo)
		kill(g->philo[i].child, SIGKILL);
//		waitpid(g->philo[i].child, &g->philo[i].child, 0);
	for (i = 0; i < 4; i++)
		pthread_join(thread[i], NULL);
	ft_end_philo(g, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_all	g;
	int		init;

	if (ft_parsing(ac, av, 0))
		return (ft_print_error("Parsing error"));
	init = ft_init_all(&g, av);
	if (init == 1)
		return (ft_print_error("Init error"));
	if (!init)
		if (ft_philosophers(&g))
			return (ft_print_error("Thread error"));
	return (init);
}
