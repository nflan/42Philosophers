/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finish_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:31:57 by nflan             #+#    #+#             */
/*   Updated: 2022/05/03 19:12:14 by nflan            ###   ########.fr       */
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
	while (!g->died)
	{
		sem_wait(g->die);
		if (ft_time_check(phil->last_meal, ft_get_time(g)) > g->tdie && !g->death->__align)
		{
			ft_action_print(g, phil->id, "died\n");
			sem_wait(g->death);
		}
		else if (g->nbeat > 0 && !g->eat->__align && g->death->__align)
			sem_wait(g->death);
		if (!g->death->__align)
			g->died = 1;
		sem_post(g->die);
		ft_usleep(1, g);
	}
	sem_post(g->forks);
	sem_close(g->forks);
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
	sem_post(g->eat);
	sem_close(g->eat);
	sem_post(g->die);
	sem_close(g->die);
//	sem_close(g->time);
	sem_close(g->print);
	exit (ret);
}
