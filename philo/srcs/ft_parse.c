/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 12:31:45 by nflan             #+#    #+#             */
/*   Updated: 2022/05/31 11:59:30 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_is_number(int ac, char **av, int error)
{
	int	i;

	while (ac-- > 1 && !error)
	{
		i = 0;
		if (av[ac][i] < 48 || av[ac][i] > 57)
		{
			if (av[ac][i] != 45 && av[ac][i++] != 43)
				error++;
			i++;
		}
		while (av[ac][i] && !error)
		{
			if ((av[ac][i] < 48 || av[ac][i] > 57) && av[ac][i] != 32)
				error++;
			i++;
		}
	}
	if (error > 0)
		ft_putstr_fd("Les parametres ne peuvent etre que des nombres\n", 2);
	return (error);
}

int	ft_parsing(int ac, char **av, int error)
{
	if (ac >= 5 && ac <= 6)
	{
		error = ft_is_number(ac, av, error);
		if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 300)
			error += ft_putstr_fd("Le programme peut avoir entre 1 et 300 philosoph\
es\n", 2);
		if (ft_atoi(av[2]) < 0)
			error += ft_putstr_fd("Le temps avant de mourir doit etre superieur ou \
egal a 0\n", 2);
		if (ft_atoi(av[3]) < 0)
			error += ft_putstr_fd("Le temps pour manger doit etre superieur ou egal\
 a 0\n", 2);
		if (ft_atoi(av[4]) < 0)
			error += ft_putstr_fd("Le temps pour dormir doit etre superieur ou egal\
 a 0\n", 2);
		if (av[5] && ft_atoi(av[5]) < 0)
			error += ft_putstr_fd("Le nombre de fois ou les philosophes doivent man\
ger doit etre superieur ou egal a 0\n", 2);
		if (error == 0)
			return (0);
	}
	else if (ac < 5)
		printf("Il manque au moins %d argument(s)\n", 5 - ac);
	else if (ac > 6)
		printf("Il y a au moins %d argument(s) en trop\n", ac - 6);
	return (1);
}
