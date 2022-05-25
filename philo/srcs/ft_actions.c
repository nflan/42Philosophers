/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 11:54:45 by nflan             #+#    #+#             */
/*   Updated: 2022/05/25 12:47:05 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_get_rest(t_phil *philo)
{
	pthread_mutex_lock(&philo->g->meal_check);
	if (!ft_check_eat(philo))
		return (1);
	pthread_mutex_unlock(&philo->g->meal_check);
	ft_action_print(philo->g, philo->id, " is sleeping\n", 0);
	ft_usleep(philo->g->tsleep * 1000);
	return (0);
}

int	ft_get_forks(t_phil *philo)
{
	pthread_mutex_lock(&philo->g->meal_check);
	if (philo->g->died)
		return (1);
	pthread_mutex_unlock(&philo->g->meal_check);
	pthread_mutex_lock(&philo->g->forks[philo->left_fork_id]);
	philo->fork_inuse[0]++;
	ft_action_print(philo->g, philo->id, " has taken a fork\n", 0);
	pthread_mutex_lock(&philo->g->forks[philo->right_fork_id]);
	philo->fork_inuse[1]++;
	ft_action_print(philo->g, philo->id, " has taken a fork\n", 0);
	return (0);
}

void	ft_get_diner(t_phil *philo)
{
	ft_action_print(philo->g, philo->id, " is eating\n", 0);
	pthread_mutex_lock(&philo->g->meal_check);
	philo->last_meal = ft_get_time();
	philo->next_meal = philo->last_meal + philo->g->tdie;
	if (philo->g->nbeat != -1)
		philo->g->eat_count++;
	pthread_mutex_unlock(&philo->g->meal_check);
	ft_usleep(philo->g->teat * 1000);
	pthread_mutex_unlock(&philo->g->forks[philo->right_fork_id]);
	philo->fork_inuse[1]--;
	pthread_mutex_unlock(&philo->g->forks[philo->left_fork_id]);
	philo->fork_inuse[0]--;
}

int	ft_check_eat(t_phil *philo)
{
	if (philo->g->nbeat != -1 && philo->g->eat_count >= philo->g->nbeat)
	{
		philo->is_dead = 1;
		philo->g->died = 1;
		return (0);
	}
	return (1);
}
