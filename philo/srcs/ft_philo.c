/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:30:07 by nflan             #+#    #+#             */
/*   Updated: 2022/05/25 12:06:28 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_one_philo(char **av)
{
	printf("0 1 has taken a fork\n");
	usleep(ft_atoi(av[2]) * 1000);
	printf("%s 1 died\n", av[2]);
	return (0);
}

int	ft_philosophers(t_all *g)
{
	t_phil	*phil;
	int		i;

	i = 0;
	phil = g->philo;
	g->first_timeval = ft_get_time();
	while (i < g->nbphilo)
	{
		phil[i].last_meal = ft_get_time();
		if (pthread_create(&phil[i].thread_id, NULL, ft_thread, &phil[i]))
			return (1);
		g->launchedphilo++;
		usleep(100);
		if (g->nbphilo % 2 == 0 && i == g->nbphilo - 2)
			i = -1;
		else if (g->nbphilo % 2 == 1 && i == g->nbphilo - 1)
			i = -1;
		i += 2;
	}
	ft_death_checker(g);
	return (0);
}

void	ft_clear_thread(t_phil *philo)
{
	if (philo->fork_inuse[1])
		pthread_mutex_unlock(&philo->g->forks[philo->right_fork_id]);
	if (philo->fork_inuse[0])
		pthread_mutex_unlock(&philo->g->forks[philo->left_fork_id]);
}

void	*ft_thread(void *arg)
{
	t_phil		*philo;

	philo = (t_phil *)arg;
	pthread_mutex_lock(&philo->g->meal_check);
	philo->next_meal = philo->g->first_timeval + philo->g->tdie;
	pthread_mutex_unlock(&philo->g->meal_check);
	if (philo->g->nbphilo % 2)
		if (philo->id == philo->g->nbphilo - 3)
			usleep(philo->g->teat * 500);
	if (philo->id % 2)
		usleep(philo->g->teat * 800);
	while (1)
	{
		if (ft_get_forks(philo))
			break ;
		ft_get_diner(philo);
		if (ft_get_rest(philo))
			break ;
		ft_action_print(philo->g, philo->id, " is thinking\n", 0);
	}
	pthread_mutex_unlock(&philo->g->meal_check);
	ft_clear_thread(philo);
	return (NULL);
}
