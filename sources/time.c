/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:53:25 by lle-briq          #+#    #+#             */
/*   Updated: 2021/09/30 18:42:21 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	t_time	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long	get_time_stamp(t_time start)
{
	long	t;
	long	s;

	t = get_time();
	s = start.tv_sec * 1000 + start.tv_usec / 1000;
	return (t - s);
}

int	everybody_alive(t_table *table)
{
	int	i;
	int	j;

	i = -1;
	while (++i < table->option.nb)
	{
		if (get_time_stamp(table->philos[i].last_meal) > table->option.time_die)
		{
			update_state(table->philos + i, DEAD);
			table->all_alive = 0;
			print_state(table->philos + i, 0);
			j = -1;
			while (++j < table->option.nb)
				pthread_mutex_unlock(&(table->forks[j]));
			return (STOP);
		}
	}
	return (CONTINUE);
}

int	waiting(long to_wait, t_table *table)
{
	long int	current;

	current = get_time();
	while (get_time() < current + to_wait && everybody_alive(table) == CONTINUE)
		usleep(100);
	return (everybody_alive(table));
}
