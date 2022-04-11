/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:07:53 by nflan             #+#    #+#             */
/*   Updated: 2022/04/11 17:07:51 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

pthread_mutex_t	lock;

void	ft_print_all(t_all *g)
{
	//	t_phil	*tmp;

	//	tmp = g->p;
	printf("g->tv_sec = %ld\n", g->tv->tv_sec);
	printf("g->tv_usec = %ld\n", g->tv->tv_usec);
	printf("tdie = %lld\n", g->tdie);
	printf("teat = %lld\n", g->teat);
	printf("tsleep = %lld\n", g->tsleep);
	//	printf("Philosophers :\n");
	//	while (tmp)
	//	{
	//		printf("%d fait %d\n", tmp->i, tmp->act);
	//		tmp = tmp->next;
	//	}
}

void	ft_clear_phil(t_phil *p)
{
	t_phil	*tmp;

	if (p)
	{
		while (p->i != 1)
			p = p->prev;
		while (p)
		{
			tmp = p;
			p = tmp->next;
			free(tmp);
		}
	}
	p = NULL;
}

int	ft_free_all(t_all *g, int code)
{
	int	i;

	i = 0;
	if (g->tv)
		free(g->tv);
	if (g->p)
		ft_clear_phil(g->p);
	//	if (g->philo)
	//		while (i++ < g->nbrp)
	//			free(g->philo);
	if (g)
		free(g);
	g = NULL;
	return (code);
}

t_all	*ft_init_all(void)
{
	t_all	*g;

	g = NULL;
	g = ft_calloc(sizeof(t_all), 1);
	if (!g)
		return (NULL);
	return (g);
}

void	ft_philadd_back(t_phil **aphil, t_phil *new)
{
	t_phil	*tmp;

	tmp = NULL;
	tmp = *aphil;
	if (aphil && new)
	{
		if (*aphil == NULL)
			*aphil = new;
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}

/*t_phil	*ft_fill_phil(t_all *g, char **av)
{
	t_phil	*ptr;
	t_phil	*new;
	t_phil	*first;

	first = NULL;
	ptr = NULL;
	new = NULL;
	first = ft_calloc(sizeof(t_phil), 1);
	if (!first)
		return (NULL);
	first->i = g->nbrp;
	first->act = 1;
	first->prev = NULL;
	first->next = NULL;
	while (++g->nbrp <= ft_atoi(av[1]))
	{
		ptr = ft_calloc(sizeof(t_phil), 1);
		if (!ptr)
			return (NULL);
		ptr->i = g->nbrp;
		ptr->act = 5;
		ptr->prev = first;
		ptr->next = new;
		new = ptr;
		first->next = ptr;
		first = first->next;
	}
	if (ptr)
		ptr->next = NULL;
	while (first->i != 1)
		first = first->prev;
	return (first);
}*/

int	ft_fill_all(t_all *g, char **av)
{
	pthread_t	thread[atoi(av[1])];
	int			tab[atoi(av[1])];

	g->tv = ft_calloc(sizeof(struct timeval), 1);
	if (!g->tv)
		return (ft_free_all(g, 1));
	g->tdie = ft_atoi(av[2]);
	g->teat = ft_atoi(av[3]);
	g->tsleep = ft_atoi(av[4]);
	g->nbrp = 1;
//	g->p = ft_fill_phil(g, av);
//	if (!g->p)
//		return (ft_free_all(g, 1));
	g->nbrp = ft_atoi(av[1]);
	g->ret = tab;
	g->philo = thread;
	g->i = 0;
	return (0);
}

long long	ft_get_time(t_all *g, int act)
{
	struct timeval	*tv;
	long long	time;

	tv = NULL;
	time = 0;
	tv = ft_calloc(sizeof(struct timeval), 1);
	if (!tv)
		return (ft_free_all(g, 1));
	if (gettimeofday(tv, g->tz) == -1)
		return (1);
	time = (tv->tv_usec - g->tv->tv_usec);
	if (act == 1)
		printf("%lld %d has taken a fork\n", time, g->i);
	else if (act == 2)
		printf("%lld %d is eating\n", time, g->i);
	else if (act == 3)
		printf("%lld %d is sleeping\n", time, g->i);
	else if (act == 4)
		printf("%lld %d is thinking\n", time, g->i);
	else if (act == 5)
		printf("%lld %d died\n", time, g->i);
	free(tv);
	return (time);
}

//valgrind --tool=helgrind ./philo pour voir les acces concurrents


void	*ft_thread(void *arg)
{
	//	char		*msg;
	t_all		*g;
	long long	time;
	pthread_mutex_init(&lock, NULL);

	g = (t_all *) arg;
	pthread_mutex_lock(&lock);
	time = ft_get_time(g, 0);
	pthread_mutex_unlock(&lock);
	while (time > 1 && time < g->tdie)
	{
		pthread_mutex_lock(&lock);
		ft_get_time(g, 1);
		time = ft_get_time(g, 0);
		if (time <= 1 && time > g->tdie)
		{
			pthread_mutex_unlock(&lock);
			ft_get_time(g, 5);
			return (NULL);
		}
		ft_get_time(g, 1);
		ft_get_time(g, 2);
		time = ft_get_time(g, 0);
		if (time <= 1 && time > g->tdie - g->teat)
		{
			pthread_mutex_unlock(&lock);
			ft_get_time(g, 5);
			return (NULL);
		}
		usleep(g->teat);
		time = ft_get_time(g, 0);
		if (time <= 1)
		{
			pthread_mutex_unlock(&lock);
			ft_get_time(g, 5);
			return (NULL);
		}
		g->tdie = g->tdie + ft_get_time(g, 0);
		printf("g->tdie = %lld\n", g->tdie);
		pthread_mutex_unlock(&lock);
		ft_get_time(g, 3);
		usleep(g->tsleep);
		time = ft_get_time(g, 0);
		printf("time = %lld\n", time);
	}
	ft_get_time(g, 5);
	printf("g->tdie = %lld\n", g->tdie);
	return (NULL);
}

int	main(int ac, char **av)
{
	pthread_t	thread[atoi(av[1])];
	int			tab[atoi(av[1])];
	//	char		*msg1 = "First Thread";
	t_all		*g;
	int			i;

	g = NULL;
	if (!ft_parsing(ac, av, 0))
		g = ft_init_all();
	if (!g)
		return (1);
	if (ft_fill_all(g, av))
		return (1);
	if (gettimeofday(g->tv, g->tz))
		return (ft_free_all(g, 1));
	for (i = 1; i <= g->nbrp; i++)
	{
		g->i++;
		tab[i] = pthread_create(&thread[i], NULL, ft_thread, (void *) g);
		if (!thread[i])
			pthread_detach(thread[i]);
	}
	//	error = ft_get_time(g, g->p);
	//	if (error)
	//		return (ft_free_all(g, 1));
	//	ft_print_all(g);
	for (i = 1; i <= g->nbrp; i++)
		pthread_join(thread[i], NULL);
	for (i = 1; i <= g->nbrp; i++)
		printf("%d Thread return %d\n", i, tab[i]);
	ft_free_all(g, 0);
	return (0);
}
