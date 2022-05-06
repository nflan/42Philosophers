/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:26:53 by nflan             #+#    #+#             */
/*   Updated: 2022/05/06 12:38:23 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

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

void	ft_usleep(unsigned int time)
{
	unsigned int	i;

	i = ft_get_time();
	while (1)
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

void	ft_putnbr(unsigned int n)
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

void	ft_action_print(t_phil *phil, int end)
{
	unsigned int	time;

	sem_wait(phil->g->print);
	time = ft_get_time() - phil->g->first_timeval;
	ft_putnbr(time);
	ft_putnbr(phil->id + 1);
//	write(1, str, ft_strlen(str));
	if (end == 1)
		write(1, "has taken a fork\n", 17);
	else if (end == 2)
		write(1, "is eating\n", 10);
	else if (end == 3)
		write(1, "is sleeping\n", 12);
	else if (end == 4)
		write(1, "is thinking\n", 12);
	else if (!end)
		write(1, "died\n", 5);
	sem_post(phil->g->print);
	if (!end)
		sem_wait(phil->g->print);
}
