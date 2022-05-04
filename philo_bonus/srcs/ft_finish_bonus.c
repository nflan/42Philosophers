/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finish_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:31:57 by nflan             #+#    #+#             */
/*   Updated: 2022/05/04 17:06:02 by nflan            ###   ########.fr       */
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
		usleep(1000);
		sem_wait(g->die);
		if (ft_time_check(phil->last_meal, ft_get_time()) > g->tdie)
		{
			ft_action_print(g, phil->id, "died\n");
			sem_wait(g->death);
			g->died = 1;
		}
		else if ((g->nbeat != -1 && !g->eat->__align) || (!g->death->__align))
			g->died = 1;
		sem_post(g->die);
	//	printf("g->eat->__align = %ld\n", g->eat->__align);
	//	printf("g->nbeat = %d\n", g->nbeat);
	//	printf("g->death->__align = %ld\n", g->death->__align);
	//	sem_wait(g->print);
	//	write(1, "forks = ", 6);
	//	ft_putnbr(g->forks->__align);
	//	write(1, "\n", 1);
	//	sem_post(g->print);
	//	write(1, "\n", 1);
	//	write(1, "death = ", 8);
	//	ft_putnbr(g->death->__align);
	//	write(1, "\n", 1);
	//	sem_post(g->print);
//		ft_usleep(1, g);
	}
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
