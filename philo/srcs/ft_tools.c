/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:58:33 by nflan             #+#    #+#             */
/*   Updated: 2022/05/02 16:12:29 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_putstr_fd(char *s, int fd)
{
	if (s)
		while (*s)
			write(fd, (void *)s++, 1);
	return (1);
}

int	ft_print_error(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	return (fd);
}

long long	ft_atoi(const char *str)
{
	unsigned int	i;
	int				minus;
	long			integer;

	i = 0;
	minus = 1;
	integer = 0;
	if (!str)
		return (-1);
	while ((str[i] > 8 && str[i] < 14) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus *= -1;
		i++;
	}
	while (str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		integer = (integer * 10) + (str[i] - '0');
		i++;
	}
	return (integer * minus);
}
