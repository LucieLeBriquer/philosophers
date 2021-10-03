/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:50:41 by lle-briq          #+#    #+#             */
/*   Updated: 2021/10/03 17:05:51 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_states(t_table *table, int i)
{
	long	time_stamp;

	pthread_mutex_lock(&(table->display));
	time_stamp = get_time_stamp(table->philos[0].start_time);
	printf("%5ld\t[%03d] all_alive = %d\n", time_stamp, i, table->all_alive);
	pthread_mutex_unlock(&(table->display));
}

void	print_msg(char *s, int i, t_table *table)
{
	long	time_stamp;

	pthread_mutex_lock(&(table->display));
	time_stamp = get_time_stamp(table->philos[0].start_time);
	printf("%5ld\t%s %d\n", time_stamp, s, i);
	pthread_mutex_unlock(&(table->display));
}

char	*get_state(int state)
{
	if (state == EATING)
		return (" eating ");
	if (state == SLEEPING)
		return ("sleeping");
	if (state == THINKING)
		return ("thinking");
	if (state == FORK)
		return ("  fork  ");
	return ("  dead  ");
}

void	print_philo_state(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&(table->display));
	printf("  Philo %d [%s]", philo->id, get_state(philo->state));
	printf("  (%d,%d)\n", philo->fork_left, philo->fork_right);
	printf("    start_time : %ld.%ld\n", philo->start_time.tv_sec,
		philo->start_time.tv_usec);
	printf("    last_meal  : %ld.%ld\n", philo->last_meal.tv_sec,
		philo->last_meal.tv_usec);
	printf("    nb_meals   : %d\n", philo->nb_meals);
	printf("    table      : %p\n", philo->table);
	pthread_mutex_unlock(&(table->display));
}

void	print_table_state(t_table *table)
{
	int	i;

	i = -1;
	printf("[GLOBAL]\n");
	printf("  option.nb  : %d\n", table->option.nb);
	printf("  time_die   : %d\n", table->option.time_die);
	printf("  time_eat   : %d\n", table->option.time_eat);
	printf("  time_sleep : %d\n", table->option.time_sleep);
	printf("  all_alive  : %d\n", table->all_alive);
	printf("[DETAILS]\n");
	while (++i < table->option.nb)
		print_philo_state((table->philos) + i, table);
}
