/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 11:49:07 by nflan             #+#    #+#             */
/*   Updated: 2022/05/09 12:30:33 by nflan            ###   ########.fr       */
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
	int				eat_count;
	unsigned int	last_meal;
	unsigned int	next_meal;
	pid_t			pid;
	struct s_all	*g;
}	t_phil;

typedef struct s_all
{
	unsigned int	tdie;
	unsigned int	teat;
	unsigned int	tsleep;
	unsigned int	first_timeval;
	int				nbphilo;
	int				nbeat;
	sem_t			*forks;
	sem_t			*death;
	sem_t			*print;
	sem_t			*die;
}	t_all;

// MAIN

// FINISH
//void		ft_death_checker(t_all *g, t_phil *phil);
void		*ft_death_checker(void *arg);
void		ft_end_philo(t_all *g, t_phil *philo);

// UTILS
unsigned int	ft_time_check(unsigned int past, unsigned int now);
unsigned int	ft_get_time(void);
void		ft_usleep(unsigned int time);
void		ft_putnbr(unsigned int n);
void		ft_action_print(t_phil *phil, int end);

// TOOLS
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_putstr_fd(char *s, int fd);
long long		ft_atoi(const char *s);
unsigned int	ft_strlen(const char *s1);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_itoa(long long nb);
char			ft_pos(int i, long long nb);
int				ft_size_long(long long nb);
// PARSE
int				ft_is_number(int ac, char **av, int error);
int				ft_parsing(int ac, char **av, int error);

#endif
