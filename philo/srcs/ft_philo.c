/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:30:07 by nflan             #+#    #+#             */
/*   Updated: 2022/05/11 18:02:15 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_philosophers(t_all *g)
{
	t_phil	*phil;
	int		i;

	i = -1;
	phil = g->philo;
	g->first_timeval = ft_get_time();
	while (++i < g->nbphilo)
	{
			phil[i].last_meal = ft_get_time();
			if (pthread_create(&phil[i].thread_id, NULL, ft_thread, &phil[i]))
				return (1);
		//	pthread_detach(phil[i].thread_id);
			usleep(100);
	}
	while (phil[i].thread_id)
	{
	}
	return (0);
}

void	ft_get_rest(t_phil *philo)
{
	ft_action_print(philo->g, philo->id, " is sleeping\n", 0);
	usleep(philo->g->tsleep * 1000);
}

void	ft_get_forks(t_phil *philo)
{
	pthread_mutex_lock(&philo->g->forks[philo->left_fork_id]);
	ft_action_print(philo->g, philo->id, " has taken a fork\n", 0);
	pthread_mutex_lock(&philo->g->forks[philo->right_fork_id]);
	ft_action_print(philo->g, philo->id, " has taken a fork\n", 0);
}

void	ft_get_diner(t_phil *philo)
{
	ft_action_print(philo->g, philo->id, " is eating\n", 0);
	pthread_mutex_lock(&philo->eat);
	pthread_mutex_lock(&philo->g->meal_check);
	philo->next_meal = ft_get_time() + philo->g->tdie;
	philo->last_meal = ft_get_time();
	if (philo->g->nbeat != -1)
		philo->g->eat_count++;
	pthread_mutex_unlock(&philo->g->meal_check);
	usleep(philo->g->teat * 1000);
	pthread_mutex_unlock(&philo->g->forks[philo->right_fork_id]);
	pthread_mutex_unlock(&philo->g->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&philo->eat);
}

void	ft_clear_thread(t_phil *philo)
{
	if (philo->g->meal_check.__align > 0)
		pthread_mutex_unlock(&philo->g->meal_check);
	if (philo->g->lock.__align > 0)
		pthread_mutex_unlock(&philo->g->lock);
	if (philo->eat.__align > 0)
		pthread_mutex_unlock(&philo->eat);
//	if (philo->g->forks[philo->right_fork_id].__align > 0)
//		pthread_mutex_unlock(&philo->g->forks[philo->right_fork_id]);
//	if (philo->g->forks[philo->left_fork_id].__align > 0)
//		pthread_mutex_unlock(&philo->g->forks[philo->left_fork_id]);
}

int	ft_check_eat(t_phil *philo)
{
	pthread_mutex_lock(&philo->g->meal_check);
	if (philo->g->nbeat != -1 && philo->g->eat_count >= philo->g->nbeat)
	{
		philo->is_dead = 1;
		pthread_mutex_unlock(&philo->g->meal_check);
	//	pthread_mutex_unlock(&philo->g->death);
		return (0);
	}
	pthread_mutex_unlock(&philo->g->meal_check);
	return (1);
}

void	*ft_thread(void *arg)
{
	t_phil		*philo;
	pthread_t	death;

	philo = (t_phil *)arg;
	philo->next_meal = ft_get_time() + philo->g->tdie;
	if (pthread_create(&death, NULL, ft_death_checker, philo))
		pthread_mutex_unlock(&philo->g->death);
	pthread_detach(death);
	if (philo->id % 2)
		usleep(philo->g->teat * 900);
	while (1)
	{
		pthread_mutex_lock(&philo->g->meal_check);
		if (philo->g->died)
		{
			pthread_mutex_unlock(&philo->g->meal_check);
			break ;
		}
		pthread_mutex_unlock(&philo->g->meal_check);
		ft_get_forks(philo);
		ft_get_diner(philo);
		if (!ft_check_eat(philo))
			break ;
		ft_get_rest(philo);
		ft_action_print(philo->g, philo->id, " is thinking\n", 0);
	}
//	ft_clear_thread(philo);
	return (NULL);
}

void	ft_philo_eats(t_phil *phil, t_all *g)
{//problems parce que l'ordre de lock est parfois 0 puis 1 et parfois 1 puis 0
	pthread_mutex_lock(&g->forks[phil->left_fork_id]);
	ft_action_print(g, phil->id, " has taken a fork\n", 0);
	pthread_mutex_lock(&g->forks[phil->right_fork_id]);
	ft_action_print(g, phil->id, " has taken a fork\n", 0);
	ft_action_print(g, phil->id, " is eating\n", 0);
	pthread_mutex_lock(&g->meal_check);
	phil->last_meal = ft_get_time();
	phil->x_ate++;
	pthread_mutex_unlock(&g->meal_check);
	ft_usleep(g->teat, g);
	pthread_mutex_unlock(&g->forks[phil->right_fork_id]);
	pthread_mutex_unlock(&g->forks[phil->left_fork_id]);
}
