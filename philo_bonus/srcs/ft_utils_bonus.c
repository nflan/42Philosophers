/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:26:53 by nflan             #+#    #+#             */
/*   Updated: 2022/05/25 12:54:33 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	ft_print_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

unsigned int	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
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

void	ft_action_print(t_phil *philo, int end)
{
	unsigned int	time;

	sem_wait(philo->g->print);
	time = ft_get_time() - philo->g->first_timeval;
	if (time <= philo->next_meal && philo->g->death->__align == 0)
	{
		ft_putnbr(time);
		ft_putnbr(philo->id + 1);
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
		if (end != 0)
			sem_post(philo->g->print);
	}
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
