/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 11:49:07 by nflan             #+#    #+#             */
/*   Updated: 2022/05/25 12:54:44 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
// waitpid
# include <sys/wait.h>
// time
# include <sys/time.h>
// kill
# include <sys/types.h>
# include <signal.h>
// threads
# include <pthread.h>
// semaphores
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

typedef struct s_phil
{
	int				id;
	unsigned int	last_meal;
	unsigned int	next_meal;
	pid_t			pid;
	struct s_all	*g;
}	t_phil;

typedef struct s_all
{
	long long		tdie;
	long long		teat;
	long long		tsleep;
	unsigned int	first_timeval;
	int				nbphilo;
	int				nbeat;
	int				eat_count;
	sem_t			*forks;
	sem_t			*death;
	sem_t			*print;
	sem_t			*take;
	sem_t			*die;
}	t_all;

// PHILO
void			ft_init_philo(t_all *g, t_phil *philo, int i);
int				ft_init_sem(t_all *g);
t_phil			*ft_init_all(t_all *g, char **av);
void			ft_routine(t_phil *philo);
int				ft_philosopher(t_all *g, t_phil *philo);

// DO IT
void			ft_get_rest(t_phil *philo);
void			ft_get_forks(t_phil *philo);
void			ft_get_diner(t_phil *philo);

// FINISH
void			*ft_death_checker(void *arg);
void			ft_end_philo(t_all *g, t_phil *philo);

// UTILS
int				ft_print_error(char *str);
unsigned int	ft_get_time(void);
void			ft_putnbr(unsigned int n);
void			ft_action_print(t_phil *philo, int end);
void			ft_usleep(long long time);

// TOOLS
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_putstr_fd(char *s, int fd);
long long		ft_atoi(const char *s);

// PARSE
int				ft_is_number(int ac, char **av, int error);
int				ft_parsing(int ac, char **av, int error);

#endif
