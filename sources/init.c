/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:53:56 by lle-briq          #+#    #+#             */
/*   Updated: 2021/09/21 17:13:56 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philosopher(t_philo *philo, int id, t_time time, t_table *table)
{
	philo->fork_left = id;
	philo->fork_right = (id + 1) % (table->option.nb);
	philo->state = THINKING;
	philo->last_meal = time;
	philo->start_time = time;
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
	table->all_alive = 1;
	if (!philo || !table->forks)
		return (ERROR_ALLOC);
	i = -1;
	while (++i < option.nb)
		pthread_mutex_init(&(table->forks[i]), NULL);
	pthread_mutex_init(&(table->display), NULL);
	i = -1;
	while (++i < option.nb)
	{
		if (init_philosopher(&(philo[i]), i, time, table))
			return (ERROR_THREAD);
	}
	i = -1;
	while (++i < option.nb)
		pthread_join(philo[i].thread, NULL);
	if (table->all_alive == 1)
		print_state(philo, 1);
	i = -1;
	while (++i < option.nb)
		pthread_mutex_destroy(&(table->forks[i]));
	return (SUCCESS);
}