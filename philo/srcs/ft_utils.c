/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:26:53 by nflan             #+#    #+#             */
/*   Updated: 2022/05/25 12:46:35 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

unsigned int	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long long time)
{
	while (time > 99999)
	{
		usleep(100000);
		time -= 100000;
	}
	usleep(time);
}

void	ft_action_print(t_all *g, int id, char *str, int end)
{
	long long	time;

	pthread_mutex_lock(&g->lock);
	time = ft_get_time() - g->first_timeval;
	pthread_mutex_lock(&g->meal_check);
	if (!g->died || end)
		printf("%lld %d%s", time, id + 1, str);
	pthread_mutex_unlock(&g->meal_check);
	pthread_mutex_unlock(&g->lock);
}
