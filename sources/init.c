/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:53:56 by lle-briq          #+#    #+#             */
/*   Updated: 2021/09/30 18:02:43 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philosophers(t_table *table, t_time time)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->option.nb)
	{
		philo = &(table->philos[i]);
		philo->fork_left = i;
		philo->fork_right = (i + 1) % (table->option.nb);
		philo->state = THINKING;
		philo->last_meal = time;
		philo->start_time = time;
		philo->nb_meals = 0;
		philo->id = i + 1;
		philo->table = table;
	}
}

static int	free_all(t_table *table)
{
	if (table->philos)
		free(table->philos);
	if (table->forks)
		free(table->forks);
	return (ERROR_ALLOC);
}

static int	init_table_bis(t_table *table, t_option option, t_time time)
{
	int		i;
	t_philo	*philo;

	init_philosophers(table, time);
	i = -1;
	while (++i < option.nb)
	{
		philo = table->philos + i;
		if (pthread_create(&(philo->thread), NULL, &routine, philo))
			return (ERROR_THREAD);
	}
	i = -1;
	while (++i < option.nb)
	{
		philo = &(table->philos[i]);
		if (pthread_join(philo->thread, NULL))
			return (ERROR_THREAD);
	}
	if (table->all_alive)
		print_state(table->philos, 1);
	i = -1;
	while (++i < option.nb)
		pthread_mutex_destroy(&(table->forks[i]));
	pthread_mutex_destroy(&(table->display));
	free_all(table);
	return (SUCCESS);
}

int	init_table(t_table *table, t_philo *philo, t_option option)
{
	int		i;
	t_time	time;

	if (gettimeofday(&time, NULL))
		return (ERROR_TIME);
	philo = malloc(option.nb * sizeof(t_philo));
	table->philos = philo;
	table->forks = malloc(option.nb * sizeof(t_mutex));
	table->option = option;
	table->all_alive = 1;
	if (!philo || !table->forks)
		return (free_all(table));
	i = -1;
	while (++i < option.nb)
		pthread_mutex_init(&(table->forks[i]), NULL);
	pthread_mutex_init(&(table->display), NULL);
	return (init_table_bis(table, option, time));
}
