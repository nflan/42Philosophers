/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:06:37 by nflan             #+#    #+#             */
/*   Updated: 2022/04/22 12:04:07 by nflan            ###   ########.fr       */
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

	i = 0;
	while (i < g->nbphilo)
	{
		g->philo[i].id = i;
		g->philo[i].x_ate = 0;
		g->philo[i].last_meal = 0;
		g->philo[i].g = g;
		i++;
	}
	return (0);
}

int	ft_init_sem(t_all *g)
{
	char	str[6] = "FORKS";
	char	dead[6] = "DEATH";
	char	eat[4] = "EAT";
	char	time[5] = "TIME";

	g->sem = str;
	g->sem_d = dead;
	g->sem_e = eat;
	g->sem_t = time;
	sem_unlink(g->sem);
	sem_unlink(g->sem_d);
	sem_unlink(g->sem_e);
	sem_unlink(g->sem_t);
	g->forks = sem_open(g->sem, O_CREAT, 0660, g->nbphilo);
	g->death = sem_open(g->sem_d, O_CREAT, 0660, 0);
	g->eat = sem_open(g->sem_e, O_CREAT, 0660, 1);
	g->time = sem_open(g->sem_t, O_CREAT, 0660, 1);
	if (g->forks == SEM_FAILED || g->death == SEM_FAILED || g->eat == SEM_FAILED)
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
	if (av[5])
		g->nbeat = ft_atoi(av[5]);
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
	ft_action_print(g, phil->id, "has taken a fork");
	sem_wait(g->forks);
	ft_action_print(g, phil->id, "has taken a fork");
	sem_wait(g->eat);
	ft_action_print(g, phil->id, "is eating");
	phil->last_meal = ft_get_time(g);
//	printf("last meal = %lld && id = %d\n", ft_time_check(g->first_timeval, phil->last_meal), phil->id + 1);
	sem_post(g->eat);
	ft_usleep(g->teat, g);
	phil->x_ate++;
	sem_post(g->forks);
	sem_post(g->forks);
	if (phil->id + 1 == g->nbphilo && phil->x_ate == g->nbeat)
		sem_post(g->death);
}

void	*ft_thread(t_all *g, t_phil *phil)
{
	phil->last_meal = g->first_timeval;
	if (pthread_create(&phil->thread_id, NULL, ft_death_checker, phil))
		return (ft_end_philo(g, 1));
	if (phil->id % 2)
		usleep(1500);
	while (!g->death->__align)
	{
		ft_philo_eats(g, phil);
		if (g->death->__align)
			break ;
		ft_action_print(g, phil->id, "is sleeping");
		ft_usleep(g->tsleep, g);
		ft_action_print(g, phil->id, "is thinking");
	}
	pthread_join(phil->thread_id, NULL);
	for (int i = 0; i < g->nbphilo; i++)
		printf("phil[i].id = %d\n", phil[i].id);
	return (ft_end_philo(g, 0));
}

int	ft_philosophers(t_all *g)
{
	t_phil	*phil;
	int		i;

	i = -1;
	phil = g->philo;
	g->first_timeval = ft_get_time(g);
//	while (++i < g->nbphilo)
//	i = -1;
	while (++i < g->nbphilo)
	{
		phil[i].child = fork();
		if ((int) phil[i].child == -1)
			return (ft_print_error("Child error"));
		else if ((int) phil[i].child == 0)
		{
			if (ft_thread(g, &phil[i]))
				return (1);
		}
	}
	i = -1;
	while (++i < g->nbphilo)
		waitpid(phil[i].child, &phil[i].child, 0);
	ft_end_philo(g, 0);
	return (0);
}

/*int	ft_philosophers(t_all *g)
{
	t_phil	*phil;
	int		i;

	i = 0;
	phil = g->philo;
	g->first_timeval = ft_get_time();
	while (i < g->nbphilo)
	{
		if (pthread_create(&phil[i].thread_id, NULL, ft_thread, &phil[i]))
			return (1);
		phil[i].last_meal = ft_get_time();
		i++;
	}
	ft_death_checker(g, g->philo);
	ft_end_philo(g, phil);
	return (0);
}*/

int	main(int ac, char **av)
{
	t_all	g;

	if (ft_parsing(ac, av, 0))
		return (ft_print_error("Parsing error"));
	if (ft_init_all(&g, av))
		return (ft_print_error("Init error"));
	if (ft_philosophers(&g))
		return (ft_print_error("Thread error"));
	return (0);
}
