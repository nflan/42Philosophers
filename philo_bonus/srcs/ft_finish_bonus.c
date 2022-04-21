/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finish_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:31:57 by nflan             #+#    #+#             */
/*   Updated: 2022/04/21 15:27:16 by nflan            ###   ########.fr       */
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
	t_all	*g;
	int		i;

	g = (t_all *)arg;
	while (!g->all_ate)
	{
		i = -1;
		while (++i < g->nbphilo && !g->died)
		{
			if (ft_time_check(g->philo[i].last_meal, ft_get_time()) > g->tdie)
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
		while (g->nbeat != -1 && i < g->nbphilo && g->philo[i].x_ate >= g->nbeat)
			i++;
		if (i == g->nbphilo)
			g->all_ate = 1;
	}
	return (NULL);
}

void	ft_end_philo(t_all *g, t_phil *phil)
{
	int	i;

	i = -1;
	while (++i < g->nbphilo)
		sem_post(g->forks);
	(void)phil;
//		kill (phil[i--].child, 9);//pthread_join(phil[i].thread_id, NULL);
	while (i-- > 0)
		kill (phil[i--].child, 15);
	sem_close(g->forks);
	sem_close(g->death);
	sem_close(g->eat);
	pthread_join(g->thread_id, NULL);
}
