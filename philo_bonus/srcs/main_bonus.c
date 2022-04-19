#include "../include/philo_bonus.h"

int	ft_print_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	main(int ac, char **av)
{
	t_all	g;

	if (ft_parsing(ac, av, 0))
		return (ft_print_error("Parsing error"));
	return (0);
}
