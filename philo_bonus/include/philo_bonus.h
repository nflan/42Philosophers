#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
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
	char			**forks;
	t_phil			philo[300];
}	t_all;

// MAIN
long long	ft_get_time(void);

// TOOLS
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_putstr_fd(char *s, int fd);
long long	ft_atoi(const char *s);

unsigned int	ft_strlen(const char *s1);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_itoa(int nb);
char			ft_pos(int i, int nb);
int				ft_size_int(int nb);
// PARSE
int			ft_is_number(int ac, char **av, int error);
int			ft_parsing(int ac, char **av, int error);

#endif
