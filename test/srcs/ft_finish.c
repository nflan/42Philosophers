/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:31:57 by nflan             #+#    #+#             */
/*   Updated: 2022/05/10 17:11:21 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_death_checker(t_all *g, t_phil *phil, int i)
{
	usleep(g->tdie * 500);
	while (1)
	{
		i = -1;
		pthread_mutex_lock(&g->meal_check);
		while (++i < g->nbphilo && !g->died)
		{
			usleep(150);
			if (ft_time_check(phil[i].last_meal, ft_get_time()) > g->tdie)
			{
				g->died = 1;
				ft_action_print(g, i, " died\n", 1);
			}
		}
		if (g->died)
		{
			pthread_mutex_unlock(&g->meal_check);
			break ;
		}
		pthread_mutex_unlock(&g->meal_check);
		i = 0;
		pthread_mutex_lock(&g->meal_check);
		while (g->nbeat != -1 && i < g->nbphilo && phil[i].x_ate >= g->nbeat)
			i++;
		if (i == g->nbphilo)
		{
			g->all_ate = 1;
			break ;
		}
		pthread_mutex_unlock(&g->meal_check);
	}
}

void	ft_end_philo(t_all *g, t_phil *phil)
{
	int	i;

	i = 0;
	while (i < g->nbphilo / 2)
	{
		if (pthread_mutex_destroy(&g->r_forks[i]))
		{
			pthread_mutex_unlock(&g->r_forks[i]);
			pthread_mutex_destroy(&g->r_forks[i]);
		}
		if (pthread_mutex_destroy(&g->l_forks[i]))
		{
			pthread_mutex_unlock(&g->l_forks[i]);
			pthread_mutex_destroy(&g->l_forks[i]);
		}
		i++;
	}
//	pthread_mutex_unlock(&g->lock);
	i = -1;
	while (++i < g->nbphilo)
		pthread_join(phil[i].thread_id, NULL);
	pthread_mutex_destroy(&g->lock);
}
