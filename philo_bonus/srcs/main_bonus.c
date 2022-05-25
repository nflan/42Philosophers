/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:06:37 by nflan             #+#    #+#             */
/*   Updated: 2022/05/25 15:08:50 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

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
		return (ft_end_philo(&g, philo), ft_print_error("Init error"));
	sem_wait(g.death);
	if (ft_philosopher(&g, philo))
		return (ft_end_philo(&g, philo), 1);
	while (1)
		if (g.death->__align)
			break ;
	ft_end_philo(&g, philo);
	return (0);
}
