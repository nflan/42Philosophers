/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:08:42 by nflan             #+#    #+#             */
/*   Updated: 2022/05/25 12:06:39 by nflan            ###   ########.fr       */
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
	int				is_dead;
	int				left_fork_id;
	int				right_fork_id;
	int				fork_inuse[2];
	unsigned int	last_meal;
	unsigned int	next_meal;
	struct s_all	*g;
	pthread_t		thread_id;
}	t_phil;

typedef struct s_all
{
	int				nbphilo;
	int				launchedphilo;
	unsigned int	tdie;
	unsigned int	teat;
	unsigned int	tsleep;
	int				nbeat;
	int				eat_count;
	int				died;
	int				all_ate;
	unsigned int	first_timeval;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	death;
	pthread_mutex_t	lock;
	pthread_mutex_t	forks[300];
	t_phil			philo[300];
}	t_all;

// MAIN

// INIT
int				ft_init_mutex(t_all *g);
void			ft_init_philo(t_all *g);
int				ft_init_all(t_all *g, char **av);

// PHILO
int				ft_one_philo(char **av);
int				ft_philosophers(t_all *g);
void			ft_clear_thread(t_phil *philo);
void			*ft_thread(void *arg);

// ACTIONS
int				ft_get_rest(t_phil *philo);
int				ft_get_forks(t_phil *philo);
void			ft_get_diner(t_phil *philo);
int				ft_check_eat(t_phil *philo);

// FINISH
void			ft_death_checker(t_all *g);
void			ft_end_philo(t_all *g);

// UTILS
unsigned int	ft_time_check(unsigned int past, unsigned int now);
unsigned int	ft_get_time(void);
void			ft_usleep(unsigned int time, t_all *g);
void			ft_action_print(t_all *g, int id, char *str, int end);

// TOOLS
int				ft_putstr_fd(char *s, int fd);
int				ft_print_error(char *str, int fd);
long long		ft_atoi(const char *s);

// PARSE
int				ft_is_number(int ac, char **av, int error);
int				ft_parsing(int ac, char **av, int error);

#endif
