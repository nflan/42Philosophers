/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:07:53 by nflan             #+#    #+#             */
/*   Updated: 2022/04/28 17:33:48 by nflan            ###   ########.fr       */
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
	if (!g.nbeat)
		return (0);
	if (ft_philosophers(&g))
		return (ft_print_error("Threads init error", 1));
	return (0);
}
