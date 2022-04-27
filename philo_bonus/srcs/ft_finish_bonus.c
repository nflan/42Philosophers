/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finish_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:31:57 by nflan             #+#    #+#             */
/*   Updated: 2022/04/27 13:29:33 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	*ft_death_checker(void *arg)
{
	t_phil	*phil;
	t_all	*g;

	phil = (t_phil *)arg;
	g = phil->g;
	while (!g->death->__align)
	{
//		printf("id = %d && last meal = %lld && time = %lld\n", phil->id, phil->last_meal, ft_get_time(g));
		if (!g->death->__align && ft_time_check(phil->last_meal, ft_get_time(g)) > g->tdie)
		{
		//	printf("temps entre last repas et mort = %lld && id = %d\n", ft_time_check(phil->last_meal, ft_get_time(g)), phil->id + 1);
			ft_action_print(g, phil->id, " died\n");
			break ;
		}
		if (phil->id % 2)
			if (g->nbeat != -1 && phil->x_ate == g->nbeat)
				break ;
//		ft_usleep(1, g);;
	}
	//if (g->forks->__align < 1)
	sem_post(g->death);
	sem_post(g->forks);
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
	sem_close(g->forks);
	sem_close(g->death);
	sem_close(g->eat);
	sem_close(g->time);
	sem_close(g->print);
	exit (ret);
}
