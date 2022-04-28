/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:30:07 by nflan             #+#    #+#             */
/*   Updated: 2022/04/28 17:42:41 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_philosophers(t_all *g)
{
	t_phil	*phil;
	int		i;

	i = -2;
	phil = g->philo;
	g->first_timeval = ft_get_time();
	while (i < g->nbphilo)
	{
		i += 2;
		if (i < g->nbphilo)
		{
			if (pthread_create(&phil[i].thread_id, NULL, ft_thread, &phil[i]))
				return (1);
			phil[i].last_meal = ft_get_time();
		}
		if (g->nbphilo % 2 && i == g->nbphilo - 1)
			i = -1;
		else if (g->nbphilo % 2 == 0 && i == g->nbphilo)
			i = -1;
	}
	ft_death_checker(g, g->philo);
	ft_end_philo(g, phil);
	return (0);
}

void	*ft_thread(void *arg)
{
	t_phil		*phil;
	t_all		*g;

	phil = (t_phil *)arg;
	g = phil->g;
	ft_action_print(g, phil->id, " is thinking\n");
	if (phil->id % 2)
	{
		usleep(g->teat * 100);
		while (g->forks[phil->right_fork_id].__align == 0
			&& g->forks[phil->left_fork_id].__align == 0)
		{
		}
	}
	while (!g->died && !g->all_ate)
	{
		ft_philo_eats(phil, g);
		ft_action_print(g, phil->id, " is sleeping\n");
		ft_usleep(g->tsleep, g);
		ft_action_print(g, phil->id, " is thinking\n");
	}
	return (NULL);
}

void	ft_philo_eats(t_phil *phil, t_all *g)
{
	pthread_mutex_lock(&g->forks[phil->left_fork_id]);
	ft_action_print(g, phil->id, " has taken a fork\n");
	pthread_mutex_lock(&g->forks[phil->right_fork_id]);
	ft_action_print(g, phil->id, " has taken a fork\n");
	ft_action_print(g, phil->id, " is eating\n");
	pthread_mutex_lock(&g->meal_check);
	phil->last_meal = ft_get_time();
	phil->x_ate++;
	pthread_mutex_unlock(&g->meal_check);
	ft_usleep(g->teat, g);
	pthread_mutex_unlock(&g->forks[phil->right_fork_id]);
	pthread_mutex_unlock(&g->forks[phil->left_fork_id]);
}
