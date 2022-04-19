#include "../include/philo_bonus.h"

int	ft_print_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	ft_init_philo(t_all *g)
{
	int	i;

	i = 0;
	while (i < g->nbphilo)
	{
		g->philo[i].id = i;
		g->philo[i].x_ate = 0;
		g->philo[i].left_fork_id = i;
		g->philo[i].right_fork_id = (i + 1) % g->nbphilo;
		g->philo[i].last_meal = 0;
		g->philo[i].g = g;
		i++;
	}
	return (0);
}

int	ft_free_all(t_all *g, int error)
{
	int	i;

	i = 0;
	if (g->forks)
	{
		if (g->forks[i])
			while (g->forks[i] && i++)
				free(g->forks[i]);
		free(g->forks);
	}
	return (error);
}

int	ft_init_forks(t_all *g)
{
	int	i;

	i = 0;
	g->forks = NULL;
	g->forks = ft_calloc(sizeof(char *), g->nbphilo - 1);
	if (!g->forks)
		return (1);
	while (i++ < g->nbphilo)
	{
		g->forks[i] = ft_strjoin("fork_", ft_itoa(i));
		if (!g->forks[i])
			return (ft_free_all(g, 1));
	}
	return (0);
}

int	ft_init_all(t_all *g, char **av)
{
	g->nbphilo = ft_atoi(av[1]);
	g->tdie = ft_atoi(av[2]);
	g->teat = ft_atoi(av[3]);
	g->tsleep = ft_atoi(av[4]);
	g->died = 0;
	g->all_ate = 0;
	if (av[5])
		g->nbeat = ft_atoi(av[5]);
	else
		g->nbeat = -1;
	if (ft_init_forks(g))
		return (1);
	ft_init_philo(g);
	return (0);
}

void	ft_print_all(t_all *g)
{
	int	i;

	i = 0;
	if (g->forks)
		while (i++ < g->nbphilo)
			printf("%s\n", g->forks[i]);
}

int	main(int ac, char **av)
{
	t_all	g;

	if (ft_parsing(ac, av, 0))
		return (ft_print_error("Parsing error"));
	if (ft_init_all(&g, av))
		return (1);
	ft_free_all(&g, 0);
	return (0);
}
