/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finish_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:31:57 by nflan             #+#    #+#             */
/*   Updated: 2022/05/06 12:33:00 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	*ft_death_checker(void *arg)
{
	t_phil	*phil;
	t_all	*g;

	phil = (t_phil *)arg;
	g = phil->g;
	usleep(g->tdie * 900);
	while (1)
	{
		sem_wait(g->die);
		if (ft_time_check(phil->last_meal, ft_get_time()) > g->tdie)
		{
			ft_action_print(phil, 0);
			sem_post(g->death);
			break ;
		}
		sem_post(g->die);
		sem_wait(g->die);
		if (g->nbeat != -1 && g->nbeat <= g->eat_count)
		{
			sem_post(g->death);
			break ;
		}
		sem_post(g->die);
	}
	return (NULL);
}

void	*ft_end_philo(t_all *g, int ret)
{
	if (ret)
	{
		sem_post(g->death);
		sem_post(g->forks);
		usleep(2000);
	}
	sem_post(g->death);
	sem_close(g->death);
	sem_post(g->forks);
	sem_close(g->forks);
	if (g->nbeat != -1)
	{
		sem_close(g->eat);
	}
	sem_close(g->die);
	sem_close(g->print);
	sem_close(g->time);
	exit (ret);
}
