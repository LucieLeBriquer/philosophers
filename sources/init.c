/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucie <lucie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 20:47:32 by lucie             #+#    #+#             */
/*   Updated: 2021/06/28 22:08:36 by lucie            ###   ########.fr       */
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

	table = (t_table *)param;
	philo = table->philo + (table->id - 1);
	if (philo->state == THINKING)
	{
		pthread_mutex_lock(&(table->forks[philo->fork_left]));
		printf("%d has taken a fork\n", philo->id);
		pthread_mutex_lock(&(table->forks[philo->fork_right]));
		printf("%d has taken a fork\n", philo->id);
		philo->state = EATING;
	}
	if (philo->state == EATING)
	{
		printf("%d start eating\n", philo->id);
		usleep(table->option.time_eat);
		pthread_mutex_unlock(&(table->forks[philo->fork_left]));
		pthread_mutex_unlock(&(table->forks[philo->fork_right]));
		philo->nb_meals++;
		philo->state = SLEEPING;
	}
	if (philo->state == SLEEPING)
	{
		printf("%d start sleeping\n", philo->id);
		usleep(table->option.time_sleep);
	}
	return (NULL);
}

static int	init_philosopher(t_philo *philo, int id, t_time time, t_table *table)
{
	philo->fork_left = id;
	philo->fork_right = (id + 1) % (table->option.nb);
	philo->state = THINKING;
	philo->last_meal = time;
	philo->nb_meals = 0;
	philo->id = id + 1;
	if (pthread_create(&(philo->thread), NULL, &stupid_routine, philo))
		return (ERROR_THREAD);
	return (SUCCESS);
}

int	init_table(t_table *table, t_option option)
{
	int		i;
	t_time	time;
	
	if (gettimeofday(&time, NULL))
		return (ERROR_TIME);
	table->philo = malloc(option.nb * sizeof(t_philo));
	table->forks = malloc(option.nb * sizeof(t_mutex));
	if (!table->philo || !table->forks)
		return (ERROR_ALLOC);
	i = -1;
	while (++i < option.nb)
		pthread_mutex_init(&(table->forks[i]), NULL);
	i = -1;
	while (++i < option.nb)
	{
		if (init_philosopher(&(table->philo[i]), i, time, table))
			return (ERROR_THREAD);
	}
	i = -1;
	while (++i < option.nb)
		pthread_join(table->philo[i].thread, NULL);
	i = -1;
	while (++i < option.nb)
		pthread_mutex_destroy(&(table->forks[i]));
	return (SUCCESS);
}