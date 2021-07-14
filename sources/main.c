/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucie <lucie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 20:10:46 by lucie             #+#    #+#             */
/*   Updated: 2021/07/14 17:41:01 by lucie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_parsing(t_option option)
{
	printf("nb[%d] die[%d] eat[%d] sleep[%d] nb_eat[%d]\n", option.nb, 
		option.time_die, option.time_eat, option.time_sleep, option.tot_meals);
}

int	main(int argc, char **argv)
{
	t_option	option;
	t_philo		philo;
	t_table		table;

	if (parse_option(&option, argc, argv))
		return (print_help());
	else
		print_parsing(option);
	init_table(&table, &philo, option);
	return (SUCCESS);
}