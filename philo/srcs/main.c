/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:07:53 by nflan             #+#    #+#             */
/*   Updated: 2022/04/20 11:32:57 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_all		g;

	if (ft_parsing(ac, av, 0))
		return (ft_print_error("Parsing error"));
	if (av[5] && ft_atoi(av[5]) == 0)
		return (0);
	ft_init_all(&g, av);
	if (ft_philosophers(&g))
		return (ft_print_error("Threads init error"));
	return (0);
}
