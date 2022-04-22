/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finish_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:31:57 by nflan             #+#    #+#             */
/*   Updated: 2022/04/22 12:02:50 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

/*void	ft_death_checker(t_all *g, t_phil *phil)
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
}*/

void	*ft_death_checker(void *arg)
{
	t_phil	*phil;
	t_all	*g;
	int		i;

	phil = (t_phil *)arg;
	g = phil->g;
//	printf("phil->thread_id = %ld\n", phil->thread_id);
	while (!g->all_ate)
	{
		i = -1;
		while (++i < g->nbphilo && !g->died)
		{
			if (ft_time_check(phil->last_meal, ft_get_time()) > g->tdie)
			{
				ft_action_print(g, i, "died");
				sem_post(g->death);
				g->died = 1;
			}
			usleep(1000);
		}
		if (g->died)
			break ;
		i = 0;
		while (g->nbeat != -1 && i < g->nbphilo && phil->x_ate >= g->nbeat)
			i++;
		if (i == g->nbphilo)
			g->all_ate = 1;
	}
//	ft_end_philo(g, phil);
	return (NULL);
}

void	*ft_end_philo(t_all *g, t_phil *phil)
{
	int	i;

	i = -1;
//	while (++i < g->nbphilo)
//		sem_post(g->forks);
	sem_close(g->forks);
	sem_close(g->death);
	sem_close(g->eat);
//	printf("phil->thread_id = %ld\n", phil->thread_id);
//	(void)phil;
	pthread_join(phil->thread_id, NULL);
	//pthread_detach(phil->thread_id);
	exit (0);
}
