/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finish_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:31:57 by nflan             #+#    #+#             */
/*   Updated: 2022/04/20 16:23:47 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

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
				ft_action_print(g, i, "died");
				sem_wait(g->death);
				g->died = 1;
			}
			usleep(1000);
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
	while (++i < g->nbfork)
		sem_post(g->forks);
	sem_post(g->death);
	sem_close(g->forks);
	sem_close(g->death);
	sem_close(g->eat);
	sem_unlink(g->sem);
	sem_unlink(g->sem_d);
	sem_unlink(g->sem_e);
	i = -1;
	while (++i < g->nbphilo)
		pthread_join(phil[i].thread_id, NULL);
}
