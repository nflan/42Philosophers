/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:30:07 by nflan             #+#    #+#             */
/*   Updated: 2022/05/10 17:23:50 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_philosophers(t_all *g)
{
	t_phil	*phil;
	int		i;

	i = -1;
	phil = g->philo;
	g->first_timeval = ft_get_time();
	while (++i < g->nbphilo)
	{
//		i += 2;
//		if (i < g->nbphilo)
//		{
			phil[i].last_meal = ft_get_time();
			if (pthread_create(&phil[i].thread_id, NULL, ft_thread, &phil[i]))
				return (1);
			//pthread_detach(phil[i].thread_id);
//		}
//		if (g->nbphilo % 2 && i == g->nbphilo - 1)
//			i = -1;
//		else if (g->nbphilo % 2 == 0 && i == g->nbphilo)
//			i = -1;
	}
	ft_death_checker(g, g->philo, 0);
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
		usleep(g->teat * 900);
	while (1)
	{
		pthread_mutex_lock(&g->meal_check);
		if (g->died || g->all_ate)
		{
			pthread_mutex_unlock(&g->meal_check);
			break ;
		}
		pthread_mutex_unlock(&g->meal_check);
		ft_philo_eats(phil, g);
		ft_action_print(g, phil->id, " is sleeping\n", 0);
		ft_usleep(g->tsleep, g);
		ft_action_print(g, phil->id, " is thinking\n", 0);
	}
	return (NULL);
}

void	ft_philo_eats(t_phil *phil, t_all *g)
{//problems parce que l'ordre de lock est parfois 0 puis 1 et parfois 1 puis 0
	if (phil->id % 2)
		pthread_mutex_lock(&g->l_forks[phil->id - 1]);
	else
		pthread_mutex_lock(&g->l_forks[phil->id]);
	ft_action_print(g, phil->id, " has taken a fork\n", 0);
	if (g->nbphilo == 1)
		usleep(g->tdie * 1005);
	if (phil->id % 2)
		pthread_mutex_lock(&g->r_forks[phil->id - 1]);
	else
		pthread_mutex_lock(&g->r_forks[phil->id]);
	ft_action_print(g, phil->id, " has taken a fork\n", 0);
	ft_action_print(g, phil->id, " is eating\n", 0);
	pthread_mutex_lock(&g->meal_check);
	phil->last_meal = ft_get_time();
	phil->x_ate++;
	pthread_mutex_unlock(&g->meal_check);
	ft_usleep(g->teat, g);
	if (phil->id % 2)
	{
		pthread_mutex_unlock(&g->r_forks[phil->id - 1]);
		pthread_mutex_unlock(&g->l_forks[phil->id - 1]);
	}
	else
	{
		pthread_mutex_unlock(&g->r_forks[phil->id]);
		pthread_mutex_unlock(&g->l_forks[phil->id]);
	}
}
