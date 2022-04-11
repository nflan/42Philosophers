/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:08:42 by nflan             #+#    #+#             */
/*   Updated: 2022/04/11 15:43:33 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_phil
{
	int				i;
	int 			act;
	struct s_phil	*prev;
	struct s_phil	*next;
}	t_phil;

typedef struct s_all
{
	struct timeval	*tv;
	struct timezone	*tz;
	long long		tdie;
	long long		teat;
	long long		tsleep;
	int				nbrp;
	t_phil			*p;
	pthread_mutex_t	lock;
	pthread_t		*philo;
	int				*ret;
	int				i;
}	t_all;

// TOOLS
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_putstr_fd(char *s, int fd);
long long	ft_atoi(const char *s);

// PARSE
int			ft_is_number(int ac, char **av, int error);
int			ft_parsing(int ac, char **av, int error);

#endif
