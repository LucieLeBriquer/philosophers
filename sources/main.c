/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:53:49 by lle-briq          #+#    #+#             */
/*   Updated: 2021/09/21 18:09:12 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, int full)
{
	long	time_stamp;
	int		id;

	time_stamp = get_time_stamp(philo->start_time);
	id = philo->id;
	pthread_mutex_lock(&(philo->table->display));
	if (full)
		printf("-- Everyone has eaten enough --\n");
	else if (philo->state == FORK)
		printf("%5ld\t%d has taken a fork\n", time_stamp, id);
	else if (philo->state == EATING)
		printf("%5ld\t%d is eating\n", time_stamp, id);
	else if (philo->state == SLEEPING)
		printf("%5ld\t%d is sleeping\n", time_stamp, id);
	else if (philo->state == THINKING)
		printf("%5ld\t%d is thinking\n", time_stamp, id);
	else
		printf("%5ld\t%d died\n", time_stamp, id);
	pthread_mutex_unlock(&(philo->table->display));
}

int	main(int argc, char **argv)
{
	t_option	option;
	t_philo		philo;
	t_table		table;

	if (parse_option(&option, argc, argv))
		return (print_help());
	init_table(&table, &philo, option);
	return (SUCCESS);
}
