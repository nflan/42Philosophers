/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_it_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:00:32 by nflan             #+#    #+#             */
/*   Updated: 2022/05/10 15:35:14 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	ft_get_rest(t_phil *philo)
{
	ft_action_print(philo, 3);
	usleep(philo->g->tsleep * 1000);
}

void	ft_get_forks(t_phil *philo)
{
	sem_wait(philo->g->take);
	sem_wait(philo->g->forks);
	ft_action_print(philo, 1);
	sem_wait(philo->g->forks);
	ft_action_print(philo, 1);
	sem_post(philo->g->take);
}

void	ft_get_diner(t_phil *philo)
{
	sem_wait(philo->g->die);
	if (ft_get_time() > philo->next_meal)
	{
		sem_post(philo->g->die);
		usleep(300);
		return ;
	}	
	ft_action_print(philo, 2);
	philo->next_meal = ft_get_time() + philo->g->tdie;
	philo->last_meal = ft_get_time();
	if (philo->g->nbeat != -1)
		philo->g->eat_count++;
	sem_post(philo->g->die);
	usleep(philo->g->teat * 1000);
	sem_post(philo->g->forks);
	sem_post(philo->g->forks);
}
