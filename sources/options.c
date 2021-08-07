/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucie <lucie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 20:12:05 by lucie             #+#    #+#             */
/*   Updated: 2021/07/17 09:04:26 by lucie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_help(void)
{
	printf("usage:\t./philo n time_die time_eat time_sleep [tot_meals]\n\n");
	printf("description:\n");
	printf("  n           the number of philosophers ");
	printf("(also the number of forks)\n");
	printf("  time_die    maximum time between two meals before starving\n");
	printf("  time_eat    time it takes to eat\n");
	printf("  time_sleep  time it takes to sleep\n");
	printf("  tot_meals   number of meals before ending the simulation\n");
	return (SUCCESS);
}

static int	ft_atoi(char *nptr)
{
	long	nb;
	int		i;

	nb = 0;
	i = 0;
	if (nptr[0] < '0' || nptr[0] > '9')
		return (FORMAT);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = 10 * nb + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] != '\0' || nb > 2147483647 || i > 10)
		return (FORMAT);
	return ((int)nb);
}

int	parse_option(t_option *option, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ERROR_PARSE);
	option->nb = ft_atoi(argv[1]);
	option->time_die = ft_atoi(argv[2]);
	option->time_eat = ft_atoi(argv[3]);
	option->time_sleep = ft_atoi(argv[4]);
	option->tot_meals = -1;
	if (argc == 6)
		option->tot_meals = ft_atoi(argv[5]);
	if (option->nb == FORMAT || option->time_die == FORMAT
			|| option->time_eat == FORMAT || option->time_sleep == FORMAT
			|| option->tot_meals == FORMAT)
		return (ERROR_PARSE);
	return (SUCCESS);
}