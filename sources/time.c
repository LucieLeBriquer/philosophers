/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:53:25 by lle-briq          #+#    #+#             */
/*   Updated: 2021/09/23 16:57:37 by lle-briq         ###   ########.fr       */
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

int		everybody_alive(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->option.nb)
	{
		if (get_time_stamp(table->philos[i].last_meal) > table->option.time_die)
		{
			table->philos[i].state = DEAD;
			table->all_alive = 0;
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

int	check_dead(t_philo *philo)
{
	if (get_time_stamp(philo->last_meal) > philo->table->option.time_die
		|| !philo->table->all_alive)
	{
		philo->state = DEAD;
		if (philo->table->all_alive)
			print_state(philo, 0);
		philo->table->all_alive = 0;
		return (1);
	}
	return (0);
}
