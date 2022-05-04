/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:26:53 by nflan             #+#    #+#             */
/*   Updated: 2022/05/04 16:29:57 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

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
	while (g->death->__align)
	{
		if (ft_time_check(i, ft_get_time()) >= time)
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
	int			len;
	int			tmp_len;
	long long	tmp;

	tmp = n;
	len = 1;
	while (tmp >= 10)
	{
		tmp = tmp / 10;
		len++;
	}
	while (len-- > 0)
	{
		tmp_len = len;
		tmp = n;
		while (tmp_len-- > 0)
			tmp = tmp / 10;
		tmp = tmp % 10;
		tmp = tmp + '0';
		write(1, &tmp, 1);
	}
	write(1, " ", 1);
}

void	ft_action_print(t_all *g, int id, char *str)
{
	long long	time;

	sem_wait(g->print);
	time = ft_get_time() - g->first_timeval;
	sem_wait(g->die);
	if (g->death->__align)
	{
		ft_putnbr(time);
		ft_putnbr(id + 1);
		write(1, str, ft_strlen(str));
	}
	sem_post(g->die);
	sem_post(g->print);
}
