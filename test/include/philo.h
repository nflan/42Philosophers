/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:08:42 by nflan             #+#    #+#             */
/*   Updated: 2022/05/11 10:55:49 by nflan            ###   ########.fr       */
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
	int				x_ate;
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
	pthread_t		thread_id[2];
	pthread_mutex_t	meal_check;
	pthread_mutex_t	print;
	pthread_mutex_t	lock;
	pthread_mutex_t	l_forks[150];
	pthread_mutex_t	r_forks[150];
	t_phil			philo[300];
}	t_all;

// MAIN

// INIT
int			ft_init_mutex(t_all *g);
int			ft_init_philo(t_all *g);
int			ft_init_all(t_all *g, char **av);

// PHILO
int			ft_philosophers(t_all *g);
void		*ft_thread(void *arg);
void		ft_philo_eats(t_phil *phil, t_all *g);

// FINISH
void		ft_death_checker(t_all *g, t_phil *phil, int i);
void		ft_end_philo(t_all *g, t_phil *phil);

// UTILS
long long	ft_time_check(long long past, long long now);
long long	ft_get_time(void);
void		ft_usleep(long long time, t_all *g);
void		ft_action_print(t_all *g, int id, char *str, int end);

// TOOLS
int			ft_putstr_fd(char *s, int fd);
int			ft_print_error(char *str, int fd);
long long	ft_atoi(const char *s);

// PARSE
int			ft_is_number(int ac, char **av, int error);
int			ft_parsing(int ac, char **av, int error);

#endif
