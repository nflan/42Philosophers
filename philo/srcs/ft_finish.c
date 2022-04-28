/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:31:57 by nflan             #+#    #+#             */
/*   Updated: 2022/04/28 17:18:37 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_death_checker(t_all *g, t_phil *phil)
{
	int	i;

	while (!g->all_ate)
	{
		i = -1;
		while (++i < g->nbphilo && !g->died)
		{
			if (ft_time_check(phil[i].last_meal, ft_get_time()) > g->tdie)
			{
				ft_action_print(g, i, " died\n");
				pthread_mutex_lock(&g->meal_check);
				g->died = 1;
				pthread_mutex_unlock(&g->meal_check);
			}
			usleep(1500);
		}
		if (g->died)
			break ;
		i = 0;
		while (g->nbeat != -1 && i < g->nbphilo && phil[i].x_ate >= g->nbeat)
			i++;
		if (i == g->nbphilo)
			g->all_ate = 1;
	}
}

void	ft_end_philo(t_all *g, t_phil *phil)
{
	int	i;

	i = -1;
	while (++i < g->nbphilo)
	{
		pthread_mutex_unlock(&g->forks[i]);
		pthread_mutex_destroy(&g->forks[i]);
	}
	i = -1;
	while (++i < g->nbphilo)
		pthread_join(phil[i].thread_id, NULL);
	pthread_mutex_destroy(&g->lock);
}
