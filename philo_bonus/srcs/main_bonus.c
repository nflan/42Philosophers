/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:06:37 by nflan             #+#    #+#             */
/*   Updated: 2022/05/09 17:22:02 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	ft_print_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

void	ft_init_philo(t_all *g, t_phil *philo, int i)
{
	philo[i].id = i;
	philo[i].g = g;
	philo[i].last_meal = 0;
	philo[i].pid = -1;
	if (g->nbeat != -1)
			philo[i].eat_count = -1;
}

int	ft_init_sem(t_all *g)
{
	sem_unlink("FORKS");
	sem_unlink("DEATH");
	sem_unlink("PRINT");
	sem_unlink("DIE");
	g->forks = sem_open("FORKS", O_CREAT, 0660, g->nbphilo);
	g->death = sem_open("DEATH", O_CREAT, 0660, 1);
	g->print = sem_open("PRINT", O_CREAT, 0660, 1);
	g->die = sem_open("DIE", O_CREAT, 0660, 1);
	if (g->forks == SEM_FAILED || g->death == SEM_FAILED || g->print == SEM_FAILED || g->die == SEM_FAILED)
		return (ft_print_error("Sem open failed"));
	return (0);
}

t_phil	*ft_init_all(t_all *g, char **av)
{
	int	i;
	t_phil	*philo;

	i = -1;
	philo = NULL;
	g->nbphilo = ft_atoi(av[1]);
	g->tdie = ft_atoi(av[2]);
	g->teat = ft_atoi(av[3]);
	g->tsleep = ft_atoi(av[4]);
	if (av[5] && ft_atoi(av[5]) >= 0)
		g->nbeat = ft_atoi(av[5]);
	else
		g->nbeat = -1;
	if (ft_init_sem(g))
		return (NULL);
	philo = malloc(sizeof(t_phil) * g->nbphilo);
	if (!philo)
		return (NULL);
	while (++i < g->nbphilo)
		ft_init_philo(g, philo, i);
	return (philo);
}

void	ft_get_forks(t_phil *philo)
{
	sem_wait(philo->g->forks);
	ft_action_print(philo, 1);
	sem_wait(philo->g->forks);
	ft_action_print(philo, 1);
}

void	ft_get_diner(t_phil *philo)
{
	ft_action_print(philo, 2);
	sem_wait(philo->g->die);
	if (philo->g->nbeat != -1)
		philo->eat_count++;
	philo->last_meal = ft_get_time();
	philo->next_meal = ft_get_time() + philo->g->tdie;
	sem_post(philo->g->die);
	usleep(philo->g->teat * 1000);
	sem_post(philo->g->forks);
	sem_post(philo->g->forks);
}

void	ft_get_rest(t_phil *philo)
{
	ft_action_print(philo, 3);
	usleep(philo->g->tsleep * 1000);
}

void	ft_routine(t_phil *philo)
{
	pthread_t	death;

	sem_wait(philo->g->die);
	philo->last_meal = ft_get_time();
	philo->next_meal = ft_get_time() + philo->g->tdie;
	sem_post(philo->g->die);
	if (philo->id % 2)
	{
		usleep(60000);
		while (ft_get_time() - philo->g->first_timeval < philo->g->teat)
		{}
	}
	if (pthread_create(&death, NULL, ft_death_checker, philo))
		sem_post(philo->g->death);
	pthread_detach(death);
	while (1)
	{
		ft_get_forks(philo);
		ft_get_diner(philo);
		ft_get_rest(philo);
		ft_action_print(philo, 4);
	}
}

int	ft_philosopher(t_all *g, t_phil *philo)
{
	int		i;

	i = -1;
	g->first_timeval = ft_get_time();
	while (++i < g->nbphilo)
	{
		philo[i].pid = fork();
		if (philo[i].pid == -1)
			return (ft_print_error("Fork error"));
		else if (philo[i].pid == 0)
		{
			ft_routine(philo + i);
			exit (0);
		}
		usleep(100);
	}
	return (0);
}

/*void	*ft_create(void *arg)
{
	t_phil	*philo;
	int		i;
	int		end;

	philo = (t_phil *)arg;
	sem_wait(philo->g->die);
	if (philo->id == 0)
	{
		i = 0;
		end = philo->g->nbphilo / 4;
	}
	else if (philo->id == 1)
	{
		i = philo->g->nbphilo / 4;
		end = philo->g->nbphilo / 4 * 2;
	}
	else if (philo->id == 2)
	{
		i = philo->g->nbphilo / 4 * 2;
		end = philo->g->nbphilo / 4 * 3;
	}
	else
	{
		i = philo->g->nbphilo / 4 * 3;
		end = philo->g->nbphilo;
	}
//	ft_putnbr(end);
//	write(1,"\n",1);
	sem_post(philo->g->die);
	while (i < end)
	{
		sem_wait(philo->g->print);
		ft_putnbr(i);
		write(1,"\n",1);
		philo[i].pid = fork();
		if (philo[i].pid == -1)
			return (NULL);
		else if (philo[i].pid == 0)
		{
			ft_routine(philo + i);
			exit (0);
		}
	//	ft_putnbr(i);
	//	write(1,"\n",1);
		i++;
		sem_post(philo->g->print);
		usleep(100);
	}
	while (1){};
	return (NULL);
}

int	ft_philosopher(t_all *g, t_phil *philo)
{
	pthread_t	thread[4];
	int			i;

	i = 0;
	g->first_timeval = ft_get_time();
	sem_wait(philo->g->die);
	while (i < 4)
	{
		if (pthread_create(&thread[i], NULL, ft_create, philo + i))
		{
			sem_post(g->death);
			return (1);
		}
		pthread_detach(thread[i]);
		i++;
	}
	sem_post(philo->g->die);
	return (0); 
}*/

int	main(int ac, char **av)
{
	t_all	g;
	t_phil	*philo;

	if (ft_parsing(ac, av, 0))
		return (ft_print_error("Parsing error"));
	if (av[5] && ft_atoi(av[5]) == 0)
		return (0);
	philo = ft_init_all(&g, av);
	if (!philo)
		return (ft_print_error("Init error"));
	sem_wait(g.death);
	if (ft_philosopher(&g, philo))
		return (ft_print_error("Thread error"));
	sem_wait(g.death);
	ft_end_philo(&g, philo);
	return (0);
}
