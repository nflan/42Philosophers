/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:26:53 by nflan             #+#    #+#             */
/*   Updated: 2022/04/28 17:59:00 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	ft_time_check(long long past, long long now)
{
	return (now - past);
}

long long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long long time, t_all *g)
{
	long long	i;

	i = ft_get_time();
	while (!g->died && !g->all_ate)
	{
		if (ft_time_check(i, ft_get_time()) >= time)
			break ;
		usleep(50);
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

void	ft_action_print(t_all *g, int id, char *str)
{
	long long	time;

	pthread_mutex_lock(&g->lock);
	if (!g->died && !g->all_ate)
	{
		time = ft_get_time() - g->first_timeval;
		printf("%lld %d %s", time, id + 1, str);
	}
	pthread_mutex_unlock(&g->lock);
}
