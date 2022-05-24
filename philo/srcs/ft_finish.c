/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:31:57 by nflan             #+#    #+#             */
/*   Updated: 2022/05/24 19:05:26 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_death_checker(t_all *g)
{
	int	i;

	usleep(g->teat * 200);
	while (1)
	{
		i = -1;
		while (++i < g->nbphilo)
		{
			pthread_mutex_lock(&g->meal_check);
			if (ft_get_time() > g->philo[i].next_meal)
			{
				g->died = 1;
				g->philo[i].is_dead = 1;
				pthread_mutex_unlock(&g->meal_check);
				ft_action_print(g, i, " died\n", 1);
				break ;
			}
			pthread_mutex_unlock(&g->meal_check);
		}
		pthread_mutex_lock(&g->meal_check);
		if (g->died)
			break;
		pthread_mutex_unlock(&g->meal_check);
	}
	pthread_mutex_unlock(&g->meal_check);
}

void	ft_end_philo(t_all *g)
{
	int	i;

	i = -1;
	while (++i < g->nbphilo)
		pthread_join(g->philo[i].thread_id, NULL);
	pthread_mutex_destroy(&g->lock);
	pthread_mutex_destroy(&g->meal_check);
	pthread_mutex_destroy(&g->death);
	i = -1;
	while (++i > g->nbphilo)
		pthread_mutex_destroy(&g->forks[i]);
}
