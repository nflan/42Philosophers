/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:26:53 by nflan             #+#    #+#             */
/*   Updated: 2022/04/21 18:14:22 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

long long	ft_time_check(long long past, long long now)
{
	return (now - past);
}

long long	ft_get_time(t_all *g)
{
	struct timeval	tv;

//	sem_wait(g->time);
(void)g;
	gettimeofday(&tv, NULL);
//	sem_post(g->time);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long long time, t_all *g)
{
	long long	i;

	i = ft_get_time(g);
	while (!g->death->__align)
	{
		if (ft_time_check(i, ft_get_time(g)) >= time)
			break ;
		usleep(50);
	}
}

void	ft_action_print(t_all *g, int id, char *str)
{
	long long	time;

	time = ft_get_time(g) - g->first_timeval;
	if (!g->death->__align)
		printf("%lld %d %s\n", time, id + 1, str);
}
