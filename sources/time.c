/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:53:25 by lle-briq          #+#    #+#             */
/*   Updated: 2021/11/22 15:41:33 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	get_time(void)
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

int	waiting(long to_wait, t_table *table)
{
	long int	current;

	current = get_time();
	while (get_time() < current + to_wait && everybody_alive(table) == CONTINUE)
		usleep(100);
	return (everybody_alive(table));
}
