/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:08:42 by nflan             #+#    #+#             */
/*   Updated: 2022/04/12 15:46:12 by nflan            ###   ########.fr       */
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
	int				id;
	int 			x_ate;
	int				left_fork_id;
	int				right_fork_id;
	long long		last_meal;
	struct s_all	*g;
	pthread_t		thread_id;
}	t_phil;

typedef struct s_all
{
	int				nbphilo;
	long long		tdie;
	long long		teat;
	long long		tsleep;
	int				nbeat;
	int				died;
	int				all_ate;
	long long		first_timeval;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	lock;
	pthread_mutex_t	forks[300];
	t_phil			philo[300];
}	t_all;

// MAIN
long long	ft_get_time(void);

// TOOLS
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_putstr_fd(char *s, int fd);
long long	ft_atoi(const char *s);

// PARSE
int			ft_is_number(int ac, char **av, int error);
int			ft_parsing(int ac, char **av, int error);

#endif
