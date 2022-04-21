/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 11:49:07 by nflan             #+#    #+#             */
/*   Updated: 2022/04/21 18:16:00 by nflan            ###   ########.fr       */
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
	int 			x_ate;
	long long		last_meal;
	struct s_all	*g;
	pthread_t		thread_id;
	pid_t			child;
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
	char			*sem_e;
	sem_t			*eat;
	char			*sem;
	sem_t			*forks;
	char			*sem_d;
	sem_t			*death;
	char			*sem_end;
	sem_t			*end;
	t_phil			philo[210];
//	pthread_t		thread_id;
}	t_all;

// MAIN

// FINISH
//void		ft_death_checker(t_all *g, t_phil *phil);
void		*ft_death_checker(void *arg);
void		ft_end_philo(t_all *g, t_phil *phil);

// UTILS
long long	ft_time_check(long long past, long long now);
long long	ft_get_time(void);
void		ft_usleep(long long time, t_all *g);
void		ft_action_print(t_all *g, int id, char *str);

// TOOLS
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_putstr_fd(char *s, int fd);
long long		ft_atoi(const char *s);

unsigned int	ft_strlen(const char *s1);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_itoa(int nb);
char			ft_pos(int i, int nb);
int				ft_size_int(int nb);
// PARSE
int				ft_is_number(int ac, char **av, int error);
int				ft_parsing(int ac, char **av, int error);

#endif
