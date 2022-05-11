/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:07:53 by nflan             #+#    #+#             */
/*   Updated: 2022/05/11 17:38:50 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_all		g;

	if (ft_parsing(ac, av, 0))
		return (ft_print_error("Parsing error", 1));
	if (av[5] && ft_atoi(av[5]) == 0)
		return (0);
	if (ft_init_all(&g, av))
		return (1);
//	pthread_mutex_lock(&g.death);
	if (ft_philosophers(&g))
		return (ft_print_error("Threads init error", 1));
//	pthread_mutex_lock(&g.death);
	ft_end_philo(&g);
	return (0);
}
