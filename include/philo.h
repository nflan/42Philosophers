/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:08:42 by nflan             #+#    #+#             */
/*   Updated: 2022/04/06 12:24:33 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

// TOOLS
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_putstr_fd(char *s, int fd);
long	ft_atoi(const char *s);

// PARSE
int		ft_is_number(int ac, char **av, int error);
int		ft_parsing(int ac, char **av, int error);

#endif
