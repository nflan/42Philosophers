/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:30:07 by nflan             #+#    #+#             */
/*   Updated: 2022/05/24 19:04:18 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_one_philo(char **av)
{
	printf("0 1 has taken a fork\n");
	usleep(ft_atoi(av[2]) * 1000);
	printf("%s 1 died\n", av[2]);
	return (0);
}

int	ft_philosophers(t_all *g)
{
	t_phil	*phil;
	int		i;

	i = 0;
	phil = g->philo;
	g->first_timeval = ft_get_time();
	while (i < g->nbphilo)
	{
		phil[i].last_meal = ft_get_time();
		if (pthread_create(&phil[i].thread_id, NULL, ft_thread, &phil[i]))
			return (1);
		g->launchedphilo++;
		usleep(100);
		if (g->nbphilo % 2 == 0 && i == g->nbphilo - 2)
			i = -1;
		else if (g->nbphilo % 2 == 1 && i == g->nbphilo)
			i = -1;
		i += 2;
	}
	ft_death_checker(g);
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
	philo->fork_inuse[0]++;
	ft_action_print(philo->g, philo->id, " has taken a fork\n", 0);
	pthread_mutex_lock(&philo->g->forks[philo->right_fork_id]);
	philo->fork_inuse[1]++;
	ft_action_print(philo->g, philo->id, " has taken a fork\n", 0);
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
	usleep(philo->g->teat * 1000);
	pthread_mutex_unlock(&philo->g->forks[philo->right_fork_id]);
	philo->fork_inuse[1]--;
	pthread_mutex_unlock(&philo->g->forks[philo->left_fork_id]);
	philo->fork_inuse[0]--;
}

void	ft_clear_thread(t_phil *philo)
{
	if (philo->fork_inuse[1])
		pthread_mutex_unlock(&philo->g->forks[philo->right_fork_id]);
	if (philo->fork_inuse[0])
		pthread_mutex_unlock(&philo->g->forks[philo->left_fork_id]);
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

void	*ft_thread(void *arg)
{
	t_phil		*philo;

	philo = (t_phil *)arg;
	philo->next_meal = philo->g->first_timeval + philo->g->tdie;
	if (philo->id % 2)
		usleep(philo->g->teat * 500);
	while (1)
	{
		pthread_mutex_lock(&philo->g->meal_check);
		if (philo->g->died)
			break ;
		pthread_mutex_unlock(&philo->g->meal_check);
		ft_get_forks(philo);
		ft_get_diner(philo);
		pthread_mutex_lock(&philo->g->meal_check);
		if (!ft_check_eat(philo))
			break ;
		pthread_mutex_unlock(&philo->g->meal_check);
		ft_get_rest(philo);
		ft_action_print(philo->g, philo->id, " is thinking\n", 0);
	}
	pthread_mutex_unlock(&philo->g->meal_check);
	ft_clear_thread(philo);
	return (NULL);
}

void	ft_philo_eats(t_phil *phil, t_all *g)
{
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
