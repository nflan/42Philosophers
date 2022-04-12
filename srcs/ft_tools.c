/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:58:33 by nflan             #+#    #+#             */
/*   Updated: 2022/04/12 11:58:22 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;

	str = s;
	if (n > 0)
		while (n--)
			*str++ = '\0';
	s = str;
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*tab;

	tab = NULL;
	tab = malloc(nmemb * size);
	if (!tab)
		return (NULL);
	ft_bzero(tab, nmemb * size);
	return (tab);
}

int	ft_putstr_fd(char *s, int fd)
{
	if (s)
		while (*s)
			write(fd, (void *)s++, 1);
	return (1);
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
