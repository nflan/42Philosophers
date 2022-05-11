/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:26:53 by nflan             #+#    #+#             */
/*   Updated: 2022/05/11 15:52:52 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

unsigned int	ft_time_check(unsigned int past, unsigned int now)
{
	return (now - past);
}

unsigned int	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(unsigned int time, t_all *g)
{
	long long	i;

	(void)g;
	i = ft_get_time();
	while (1)
	{
		if (ft_time_check(i, ft_get_time()) >= time)
			break ;
		usleep(500);
	}
}

void	ft_action_print(t_all *g, int id, char *str, int end)
{
	long long	time;

	pthread_mutex_lock(&g->lock);
	time = ft_get_time() - g->first_timeval;
	printf("%lld %d%s", time, id + 1, str);
	if (!end)
		pthread_mutex_unlock(&g->lock);
}
