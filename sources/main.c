/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:53:49 by lle-briq          #+#    #+#             */
/*   Updated: 2021/10/03 17:00:05 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_option	option;
	t_philo		philo;
	t_table		table;

	if (parse_option(&option, argc, argv))
		return (print_help());
	return (init_table(&table, &philo, option));
}
