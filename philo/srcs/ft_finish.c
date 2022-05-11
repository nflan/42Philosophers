/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:31:57 by nflan             #+#    #+#             */
/*   Updated: 2022/05/11 17:56:54 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*ft_death_checker(void *arg)
{
	t_phil	*philo;

	philo = (t_phil *)arg;
	usleep(philo->g->tdie * 900);
	while (1)
	{
		pthread_mutex_lock(&philo->g->meal_check);
		if (ft_get_time() > philo->next_meal)
		{
			ft_action_print(philo->g, philo->id, " died\n", 1);
			philo->g->died = 1;
		//	pthread_mutex_unlock(&philo->g->death);
			break ;
		}
		pthread_mutex_unlock(&philo->g->meal_check);
		usleep(100);
	}
	pthread_mutex_unlock(&philo->g->meal_check);
	return (NULL);
}

void	ft_end_philo(t_all *g)
{
	int	i;

	i = -1;
	while (++i < g->nbphilo)
		pthread_join(g->philo[i].thread_id, NULL);
//	pthread_mutex_unlock(&g->lock);
	pthread_mutex_destroy(&g->lock);
	pthread_mutex_destroy(&g->meal_check);
//	pthread_mutex_unlock(&g->death);
	pthread_mutex_destroy(&g->death);
	i = -1;
	while (++i < g->nbphilo)
	{
		pthread_mutex_destroy(&g->forks[i]);
	//	pthread_mutex_unlock(&g->philo[i].eat);
		pthread_mutex_destroy(&g->philo[i].eat);
	}
}
