/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:06:37 by nflan             #+#    #+#             */
/*   Updated: 2022/04/27 13:28:45 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	ft_print_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	ft_init_philo(t_all *g, t_phil *phil, int i)
{
//	int	i;
//
//	i = 0;
//	while (i < g->nbphilo)
//	{
	phil->id = i;
	phil->x_ate = 0;
	phil->g = g;
	phil->last_meal = ft_get_time(g);
	g->philo[i] = *phil;
	if (pthread_create(&phil->thread_id, NULL, ft_death_checker, phil))
		return (1);
//	}
	return (0);
}

int	ft_init_sem(t_all *g)
{
	char	str[6] = "FORKS";
	char	dead[6] = "DEATH";
	char	eat[4] = "EAT";
	char	print[6] = "PRINT";
//	char	time[5] = "TIME";

	g->sem = str;
	g->sem_d = dead;
	g->sem_e = eat;
	g->sem_p = print;
	sem_unlink(g->sem);
	sem_unlink(g->sem_d);
	sem_unlink(g->sem_e);
	sem_unlink(g->sem_p);
	g->forks = sem_open(g->sem, O_CREAT, 0660, g->nbphilo);
	g->death = sem_open(g->sem_d, O_CREAT, 0660, 0);
	g->eat = sem_open(g->sem_e, O_CREAT, 0660, 1);
	g->print = sem_open(g->sem_p, O_CREAT, 0660,1);
//	g->sem_t = time;
//	sem_unlink(g->sem_t);
//	g->time = sem_open(g->sem_t, O_CREAT, 0660, g->nbphilo);
//	if (g->time == SEM_FAILED)
//		return (ft_print_error("Sem open failed"));
	if (g->forks == SEM_FAILED || g->death == SEM_FAILED || g->eat == SEM_FAILED || g->print == SEM_FAILED)
		return (ft_print_error("Sem open failed"));
	return (0);
}

int	ft_init_all(t_all *g, char **av)
{

	g->nbphilo = ft_atoi(av[1]);
	g->tdie = ft_atoi(av[2]);
	g->teat = ft_atoi(av[3]);
	g->tsleep = ft_atoi(av[4]);
	g->died = 0;
	if (av[5] && ft_atoi(av[5]) >= 0)
	{
		if (ft_atoi(av[5]) == 0)
			return (2);
		g->nbeat = ft_atoi(av[5]);
	}
	else
		g->nbeat = -1;
	if (ft_init_sem(g))
		return (1);
	//ft_init_philo(g);
	return (0);
}

void	ft_philo_eats(t_all *g, t_phil *phil)
{
	sem_wait(g->forks);
	ft_action_print(g, phil->id, " has taken a fork\n");
	sem_wait(g->forks);
	ft_action_print(g, phil->id, " has taken a fork\n");
	ft_action_print(g, phil->id, " is eating\n");
	sem_wait(g->eat);
	phil->last_meal = ft_get_time(g);
//	printf("last meal = %lld && id = %d\n", ft_time_check(g->first_timeval, phil->last_meal), phil->id + 1);
	phil->x_ate++;
	sem_post(g->eat);
	ft_usleep(g->teat, g);
	sem_post(g->forks);
	sem_post(g->forks);
}

void	*ft_thread(t_all *g, t_phil phil, int i)
{
//	phil->last_meal = g->first_timeval;
//	printf("i = %d\n", i);
	if (ft_init_philo(g, &phil, i))
		return (ft_end_philo(g, 1));
	if (phil.id % 2)
	{
		usleep(g->teat * 100);
		while (g->forks->__align == 0 && g->forks->__align == 0)
		{
		}
	}
	while (!g->death->__align)
	{
		ft_philo_eats(g, &phil);
		if (g->death->__align)
			break ;
		ft_action_print(g, phil.id, " is sleeping\n");
		ft_usleep(g->tsleep, g);
		ft_action_print(g, phil.id, " is thinking\n");
	}
	pthread_join(phil.thread_id, NULL);
//	for (int i = 0; i < g->nbphilo; i++)
//		printf("g->phil[i].id = %d\n", g->philo[i].id);
	return (ft_end_philo(g, 0));
}

int	ft_philosophers(t_all *g)
{
//	t_phil	*phil;
	int		i;

	i = -2;
	g->first_timeval = ft_get_time(g);
//	while (++i < g->nbphilo)
//	i = -1;
	while (i < g->nbphilo)
	{
		i += 2;
		g->philo[i].child = fork();
		if ((int) g->philo[i].child == -1)
			return (ft_print_error("Child error"));
		else if ((int) g->philo[i].child == 0)
			if (ft_thread(g, g->philo[i], i))
				return (1);
		if (g->nbphilo % 2 && i == g->nbphilo - 1)
			i = -1;
		else if (g->nbphilo % 2 == 0 && i == g->nbphilo)
			i = -1;
	}
	i = -1;
	while (++i < g->nbphilo)
		waitpid(g->philo[i].child, &g->philo[i].child, 0);
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
