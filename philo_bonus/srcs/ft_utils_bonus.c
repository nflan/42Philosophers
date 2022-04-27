/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:26:53 by nflan             #+#    #+#             */
/*   Updated: 2022/04/27 12:57:46 by nflan            ###   ########.fr       */
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

	(void)g;
	gettimeofday(&tv, NULL);
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

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(long long n)
{
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(n + '0');
}

void	ft_action_print(t_all *g, int id, char *str)
{
	long long	time;
//	char		*tps;
//	char		*i;

//	i = ft_itoa(id);
//	tps = ft_itoa(time);
	sem_wait(g->print);
	time = ft_get_time(g) - g->first_timeval;
	if (!g->death->__align)
	{
		ft_putnbr(time);
//		write(1, tps, ft_strlen(tps));
		write(1, " ", 1);
	//	write(1, i, ft_strlen(tps));
		ft_putnbr(id + 1);
		write(1, str, ft_strlen(str));
	}
	sem_post(g->print);
}
