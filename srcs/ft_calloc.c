/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:58:33 by nflan             #+#    #+#             */
/*   Updated: 2022/04/05 15:15:31 by nflan            ###   ########.fr       */
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
