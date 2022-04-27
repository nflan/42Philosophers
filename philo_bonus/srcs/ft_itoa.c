/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:06:51 by nflan             #+#    #+#             */
/*   Updated: 2022/04/27 12:24:55 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	ft_size_long(long long nb)
{
	long long	number;
	int			base_len;
	int			number_len;

	number_len = 0;
	base_len = 10;
	if (nb < 0)
		number = -nb;
	else
		number = nb;
	while (number >= base_len)
	{
		number = number / base_len;
		number_len++;
	}
	number_len++;
	return (number_len);
}

char	ft_pos(int i, long long nb)
{
	char			pos;
	unsigned int	nombre;
	unsigned int	base_len;

	base_len = 10;
	if (nb < 0)
		nombre = nb * -1;
	else
		nombre = nb;
	while (i > 1)
	{
		nombre = nombre / base_len;
		i--;
	}
	pos = nombre % base_len + '0';
	return (pos);
}

char	*ft_itoa(long long nb)
{
	char	*str;
	int		int_len;
	int		i;
	int		len;

	i = 0;
	int_len = ft_size_long(nb);
	len = int_len;
	if (nb < 0)
		len++;
	str = ft_calloc(sizeof(*str), (len + 1));
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		str[0] = '-';
		i++;
	}
	while (int_len)
	{
		str[i] = ft_pos(int_len, nb);
		int_len--;
		i++;
	}
	return (str);
}
