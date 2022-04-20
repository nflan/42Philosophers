/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:30:07 by nflan             #+#    #+#             */
/*   Updated: 2022/04/20 11:30:57 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_philosophers(t_all *g)
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
}

void	*ft_thread(void *arg)
{
	t_phil		*phil;
	t_all		*g;

	phil = (t_phil *)arg;
	g = phil->g;
	if (phil->id % 2)
		usleep(1500);
	while (!g->died && !g->all_ate)
	{
		ft_philo_eats(g, phil);
		if (g->all_ate || g->died)
			break ;
		ft_action_print(g, phil->id, "is sleeping");
		ft_usleep(g->tsleep, g);
		ft_action_print(g, phil->id, "is thinking");
	}
	return (NULL);
}

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
	if (phil->id + 1 == g->nbphilo && phil->x_ate == g->nbeat)
		g->all_ate = 1;
}
