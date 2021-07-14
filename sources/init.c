/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucie <lucie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 20:47:32 by lucie             #+#    #+#             */
/*   Updated: 2021/07/14 17:54:21 by lucie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philosopher(t_philo *philo, int id, t_time time, t_table *table)
{
	philo->fork_left = id;
	philo->fork_right = (id + 1) % (table->option.nb);
	philo->state = THINKING;
	philo->last_meal = time;
	philo->nb_meals = 0;
	philo->id = id + 1;
	philo->table = table;
	if (pthread_create(&(philo->thread), NULL, &routine, philo))
		return (ERROR_THREAD);
	return (SUCCESS);
}

int	init_table(t_table *table, t_philo *philo, t_option option)
{
	int		i;
	t_time	time;
	
	if (gettimeofday(&time, NULL))
		return (ERROR_TIME);
	philo = malloc(option.nb * sizeof(t_philo));
	table->forks = malloc(option.nb * sizeof(t_mutex));
	table->option = option;
	if (!philo || !table->forks)
		return (ERROR_ALLOC);
	i = -1;
	while (++i < option.nb)
		pthread_mutex_init(&(table->forks[i]), NULL);
	i = -1;
	while (++i < option.nb)
	{
		if (init_philosopher(&(philo[i]), i, time, table))
			return (ERROR_THREAD);
	}
	i = -1;
	while (++i < option.nb)
		pthread_join(philo[i].thread, NULL);
	i = -1;
	while (++i < option.nb)
		pthread_mutex_destroy(&(table->forks[i]));
	return (SUCCESS);
}