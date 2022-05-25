/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:04:03 by nflan             #+#    #+#             */
/*   Updated: 2022/05/25 12:22:02 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	ft_init_philo(t_all *g, t_phil *philo, int i)
{
	philo[i].id = i;
	philo[i].g = g;
	philo[i].last_meal = 0;
	philo[i].pid = -1;
}

int	ft_init_sem(t_all *g)
{
	sem_unlink("FORKS");
	sem_unlink("DEATH");
	sem_unlink("PRINT");
	sem_unlink("TAKE");
	sem_unlink("DIE");
	g->forks = sem_open("FORKS", O_CREAT, 0660, g->nbphilo);
	g->death = sem_open("DEATH", O_CREAT, 0660, 1);
	g->print = sem_open("PRINT", O_CREAT, 0660, 1);
	g->take = sem_open("TAKE", O_CREAT, 0660, 1);
	g->die = sem_open("DIE", O_CREAT, 0660, 1);
	if (g->forks == SEM_FAILED || g->death == SEM_FAILED
		|| g->print == SEM_FAILED || g->die == SEM_FAILED
		|| g->take == SEM_FAILED)
		return (ft_print_error("Sem open failed"));
	return (0);
}

t_phil	*ft_init_all(t_all *g, char **av)
{
	int		i;
	t_phil	*philo;

	i = -1;
	philo = NULL;
	g->nbphilo = ft_atoi(av[1]);
	g->tdie = ft_atoi(av[2]);
	g->teat = ft_atoi(av[3]);
	g->tsleep = ft_atoi(av[4]);
	g->eat_count = -1;
	if (av[5] && ft_atoi(av[5]) >= 0)
		g->nbeat = ft_atoi(av[5]);
	else
		g->nbeat = -1;
	if (ft_init_sem(g))
		return (NULL);
	philo = malloc(sizeof(t_phil) * g->nbphilo);
	if (!philo)
		return (NULL);
	while (++i < g->nbphilo)
		ft_init_philo(g, philo, i);
	return (philo);
}

void	ft_routine(t_phil *philo)
{
	pthread_t	death;

	philo->last_meal = ft_get_time();
	philo->next_meal = ft_get_time() + philo->g->tdie;
	if (philo->id % 2)
		usleep(philo->g->teat * 800);
	if (pthread_create(&death, NULL, ft_death_checker, philo))
		sem_post(philo->g->death);
	pthread_detach(death);
	while (1)
	{
		ft_get_forks(philo);
		ft_get_diner(philo);
		ft_get_rest(philo);
		ft_action_print(philo, 4);
	}
}

int	ft_philosopher(t_all *g, t_phil *philo)
{
	int		i;

	i = -1;
	g->first_timeval = ft_get_time();
	while (++i < g->nbphilo)
	{
		philo[i].pid = fork();
		if (philo[i].pid == -1)
			return (ft_print_error("Fork error"));
		else if (philo[i].pid == 0)
		{
			ft_routine(philo + i);
			exit (0);
		}
		usleep(100);
	}
	return (0);
}
