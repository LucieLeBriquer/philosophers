/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:53:49 by lle-briq          #+#    #+#             */
/*   Updated: 2021/10/03 17:09:09 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_state(t_philo *philo, int state)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&(table->display));
	if (philo->state != DEAD)
	{
		philo->state = state;
		if (state == EATING)
			gettimeofday(&(philo->last_meal), NULL);
	}
	pthread_mutex_unlock(&(table->display));
}

static int	everyone_is_full(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->option.nb)
		if (table->philos[i].nb_meals < table->option.tot_meals
			|| table->option.tot_meals == -1)
			return (0);
	return (1);
}

static void	print_state_msg(t_philo *philo, long time_stamp, int id,
	int *print_end)
{
	if (everyone_is_full(philo->table))
	{
		printf("-- Everyone has eaten enough --\n");
		*print_end = 1;
	}
	else if (philo->state == DEAD)
	{
		printf("%5ld\t%d died\n", time_stamp, id);
		*print_end = 1;
	}
	else if (philo->state == FORK && philo->table->all_alive)
		printf("%5ld\t%d has taken a fork\n", time_stamp, id);
	else if (philo->state == EATING)
		printf("%5ld\t%d is eating\n", time_stamp, id);
	else if (philo->state == SLEEPING)
		printf("%5ld\t%d is sleeping\n", time_stamp, id);
	else if (philo->state == THINKING)
		printf("%5ld\t%d is thinking\n", time_stamp, id);
}

void	print_state(t_philo *philo)
{
	static int	print_end;
	long		time_stamp;
	int			id;

	pthread_mutex_lock(&(philo->table->display));
	if (!print_end)
	{
		id = philo->id;
		time_stamp = get_time_stamp(philo->start_time);
		print_state_msg(philo, time_stamp, id, &print_end);
	}
	pthread_mutex_unlock(&(philo->table->display));
}
