/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:53:49 by lle-briq          #+#    #+#             */
/*   Updated: 2021/10/30 16:59:00 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_state(t_philo *philo, int state)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&(table->m_state));
	if (philo->state != DEAD)
	{
		philo->state = state;
		if (state == EATING)
			gettimeofday(&(philo->last_meal), NULL);
		pthread_mutex_unlock(&(table->m_state));
		return ;
	}
	pthread_mutex_unlock(&(table->m_state));
}

static void	print_state_msg(t_philo *philo, long time_stamp, int id,
	int *print_end)
{
	int	state;

	pthread_mutex_lock(&(philo->table->m_state));
	state = philo->state;
	pthread_mutex_unlock(&(philo->table->m_state));
	if (everyone_is_full(philo->table))
	{
		printf("-- Everyone has eaten enough --\n");
		*print_end = 1;
	}
	else if (state == DEAD)
	{
		printf("%5ld\t%d died\n", time_stamp, id);
		*print_end = 1;
	}
	else if (state == FORK && everybody_alive(philo->table))
		printf("%5ld\t%d has taken a fork\n", time_stamp, id);
	else if (state == EATING)
		printf("%5ld\t%d is eating\n", time_stamp, id);
	else if (state == SLEEPING)
		printf("%5ld\t%d is sleeping\n", time_stamp, id);
	else if (state == THINKING)
		printf("%5ld\t%d is thinking\n", time_stamp, id);
}

void	print_state(t_philo *philo)
{
	static int	print_end;
	long		time_stamp;
	int			id;

	time_stamp = get_time_stamp(philo->start_time);
	id = philo->id;
	pthread_mutex_lock(&(philo->table->m_display));
	if (!print_end)
		print_state_msg(philo, time_stamp, id, &print_end);
	pthread_mutex_unlock(&(philo->table->m_display));
}
