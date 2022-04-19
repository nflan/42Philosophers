/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:14:31 by nflan             #+#    #+#             */
/*   Updated: 2021/12/07 08:30:55 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

unsigned int	ft_strlen(char const *s1)
{
	unsigned int	i;

	i = 0;
	if (s1)
		while (s1[i])
			i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	len;
	char			*new;

	len = 0;
	new = NULL;
	if (s1 && s2)
	{
		len = ft_strlen(s1) + ft_strlen(s2);
		new = ft_calloc(sizeof(char), len + 1);
		if (!new)
			return (NULL);
		while (*s1)
			*new++ = *s1++;
		while (*s2)
			*new++ = *s2++;
		*new = '\0';
	}
	return (new - len);
}
