/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:53:25 by lle-briq          #+#    #+#             */
/*   Updated: 2021/09/21 20:09:44 by lle-briq         ###   ########.fr       */
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

void	waiting(long to_wait, t_table *table)
{
	long int	current;

	current = get_time();
	while (get_time() < current + to_wait && table->all_alive)
		usleep(100);
}

int	check_dead(t_philo *philo)
{
	//pthread_mutex_lock(&(philo->table->display));
	//printf("last meal of %d was %ld ago\n", philo->id, get_time_stamp(philo->last_meal));
	//pthread_mutex_unlock(&(philo->table->display));
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
