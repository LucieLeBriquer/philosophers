/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:53:49 by lle-briq          #+#    #+#             */
/*   Updated: 2021/09/21 17:24:07 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*static void	print_parsing(t_option option)
{
	printf("nb[%d] die[%d] eat[%d] sleep[%d] nb_eat[%d]\n", option.nb, 
		option.time_die, option.time_eat, option.time_sleep, option.tot_meals);
}*/

void	print_state(t_philo *philo, int full)
{
	pthread_mutex_lock(&(philo->table->display));
	if (full)
		printf("-- Everyone has eaten enough --\n");
	else if (philo->state == FORK)
		printf("%5ld\t%d has taken a fork\n", get_time_stamp(philo->start_time), philo->id);
	else if (philo->state == EATING)
		printf("%5ld\t%d is eating\n", get_time_stamp(philo->start_time), philo->id);
	else if (philo->state == SLEEPING)
		printf("%5ld\t%d is sleeping\n", get_time_stamp(philo->start_time), philo->id);
	else if (philo->state == THINKING)
		printf("%5ld\t%d is thinking\n", get_time_stamp(philo->start_time), philo->id);
	else
		printf("%5ld\t%d died\n", get_time_stamp(philo->start_time), philo->id);
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