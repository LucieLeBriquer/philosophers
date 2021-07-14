/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucie <lucie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 17:39:17 by lucie             #+#    #+#             */
/*   Updated: 2021/07/14 18:02:22 by lucie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*stupid_routine(void *param)
{
	t_philo	philo;

	philo = *(t_philo *)param;
	printf("i'm philo %d, my last meal was at %ld:%ld\n", philo.id, philo.last_meal.tv_sec, philo.last_meal.tv_usec);
	printf("i'm philo %d, my forks are %d and %d\n", philo.id, philo.fork_left, philo.fork_right);
	return (NULL);
}

void	*routine(void *param)
{
	t_philo	*philo;
	t_table	*table;
	t_time	time;
	
	philo = (t_philo *)param;
	table = philo->table;
	if (philo->state == THINKING)
	{
		pthread_mutex_lock(&(table->forks[philo->fork_left]));
		gettimeofday(&time, NULL);
		printf("%ld:%ld ", time.tv_sec, time.tv_usec);
		printf("%d has taken a fork\n", philo->id);
		pthread_mutex_lock(&(table->forks[philo->fork_right]));
		gettimeofday(&time, NULL);
		printf("%ld:%ld ", time.tv_sec, time.tv_usec);
		printf("%d has taken a fork\n", philo->id);
		philo->state = EATING;
	}
	if (philo->state == EATING)
	{
		gettimeofday(&time, NULL);
		printf("%ld:%ld ", time.tv_sec, time.tv_usec);
		printf("%d start eating\n", philo->id);
		usleep(table->option.time_eat);
		pthread_mutex_unlock(&(table->forks[philo->fork_left]));
		pthread_mutex_unlock(&(table->forks[philo->fork_right]));
		gettimeofday(&time, NULL);
		printf("%ld:%ld ", time.tv_sec, time.tv_usec);
		printf("%d done eating\n", philo->id);
		philo->nb_meals++;
		if (philo->nb_meals == table->option.tot_meals)
			return (NULL);
		philo->state = SLEEPING;
	}
	if (philo->state == SLEEPING)
	{
		gettimeofday(&time, NULL);
		printf("%ld:%ld ", time.tv_sec, time.tv_usec);
		printf("%d start sleeping\n", philo->id);
		usleep(table->option.time_sleep);
		gettimeofday(&time, NULL);
		printf("%ld:%ld ", time.tv_sec, time.tv_usec);
		printf("%d done sleeping\n", philo->id);
		philo->state = THINKING;
	}
	if (philo->state != DEAD)
		routine(philo);
	return (NULL);
}