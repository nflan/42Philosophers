/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:25:00 by nflan             #+#    #+#             */
/*   Updated: 2022/05/25 12:45:57 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_init_mutex(t_all *g)
{
	int	i;

	i = -1;
	while (++i < g->nbphilo)
		if (pthread_mutex_init(&g->forks[i], NULL))
			return (1);
	if (pthread_mutex_init(&g->lock, NULL))
		return (1);
	if (pthread_mutex_init(&g->death, NULL))
		return (1);
	if (pthread_mutex_init(&g->meal_check, NULL))
		return (1);
	return (0);
}

void	ft_init_philo(t_all *g)
{
	int	i;

	i = -1;
	while (++i < g->nbphilo)
	{
		g->philo[i].id = i;
		g->philo[i].x_ate = 0;
		if (i < (i + 1) % g->nbphilo)
		{
			g->philo[i].left_fork_id = i;
			g->philo[i].right_fork_id = (i + 1) % g->nbphilo;
		}
		else
		{
			g->philo[i].right_fork_id = i;
			g->philo[i].left_fork_id = (i + 1) % g->nbphilo;
		}
		g->philo[i].last_meal = 0;
		g->philo[i].g = g;
		g->philo[i].is_dead = 0;
		g->philo[i].fork_inuse[0] = 0;
		g->philo[i].fork_inuse[1] = 0;
	}
}

int	ft_init_all(t_all *g, char **av)
{
	g->nbphilo = ft_atoi(av[1]);
	g->tdie = ft_atoi(av[2]);
	g->teat = ft_atoi(av[3]);
	g->tsleep = ft_atoi(av[4]);
	g->launchedphilo = 0;
	g->died = 0;
	g->all_ate = 0;
	g->eat_count = 0;
	if (av[5] && ft_atoi(av[5]) >= 0)
		g->nbeat = ft_atoi(av[5]) * g->nbphilo;
	else
		g->nbeat = -1;
	if (ft_init_mutex(g))
		return (ft_print_error("Mutex error\n", 1));
	ft_init_philo(g);
	return (0);
}
