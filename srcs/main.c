/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:07:53 by nflan             #+#    #+#             */
/*   Updated: 2022/04/07 18:06:13 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_print_all(t_all *g)
{
//	t_phil	*tmp;

//	tmp = g->p;
	printf("g->tv_sec = %ld\n", g->tv->tv_sec);
	printf("g->tv_usec = %d\n", g->tv->tv_usec);
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
	if (g->tv)
		free(g->tv);
	if (g->p)
		ft_clear_phil(g->p);
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

t_phil	*ft_fill_phil(t_all *g, char **av)
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
}

int	ft_fill_all(t_all *g, char **av)
{
	g->tv = ft_calloc(sizeof(struct timeval), 1);
	if (!g->tv)
		return (ft_free_all(g, 1));
	if (gettimeofday(g->tv, g->tz))
		return (ft_free_all(g, 1));
	g->tdie = ft_atoi(av[2]);
	g->teat = ft_atoi(av[3]);
	g->tsleep = ft_atoi(av[4]);
	g->nbrp = 1;
	g->p = ft_fill_phil(g, av);
	if (!g->p)
		return (ft_free_all(g, 1));
	return (0);
}

int	ft_get_time(t_all *g, t_phil *p)
{
	struct timeval	*tv;
	float			time;

	tv = NULL;
	time = 0;
	tv = ft_calloc(sizeof(struct timeval), 1);
	if (!tv)
		return (ft_free_all(g, 1));
	if (gettimeofday(tv, g->tz))
		return (1);
	time = ((float)tv->tv_usec - (float)g->tv->tv_usec) / 1000;
	if (p->act == 1)
		printf("%0.3f %d has taken a fork\n", time, p->i);
	else if (p->act == 2)
		printf("%0.3f %d is eating\n", time, p->i);
	else if (p->act == 3)
		printf("%0.3f %d is sleeping\n", time, p->i);
	else if (p->act == 4)
		printf("%0.3f %d is thinking\n", time, p->i);
	else if (p->act == 5)
		printf("%0.3f %d died\n", time, p->i);
	free(tv);
	return (0);
}

//valgrind --tool=helgrind ./philo pour voir les acces concurrents

int	main(int ac, char **av)
{
	t_all		*g;
	int			error;
	pthread_t	threadIDs[ft_atoi(av[1])];

	g = NULL;
	if (!ft_parsing(ac, av, 0))
		g = ft_init_all();
	if (!g)
		return (1);
	if (ft_fill_all(g, av))
		return (1);
	usleep(1000);
	error = ft_get_time(g, g->p);
	if (error)
		return (ft_free_all(g, 1));
	ft_print_all(g);
	ft_free_all(g, 0);
	return (0);
}
