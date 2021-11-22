/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:53:56 by lle-briq          #+#    #+#             */
/*   Updated: 2021/11/22 16:16:45 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	free_all(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->option.nb)
		pthread_mutex_destroy(&(table->forks[i]));
	pthread_mutex_destroy(&(table->m_display));
	pthread_mutex_destroy(&(table->m_all_alive));
	pthread_mutex_destroy(&(table->m_state));
	pthread_mutex_destroy(&(table->m_nb_meals));
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
	while (all_alive_and_hungry(table) == CONTINUE)
		usleep(100);
	i = -1;
	while (++i < option.nb)
	{
		philo = table->philos + i;
		if (pthread_join(philo->thread, NULL))
			return (ERROR_THREAD);
	}
	free_all(table);
	return (SUCCESS);
}

static void	init_global_mutex(t_table *table)
{
	pthread_mutex_init(&(table->m_display), NULL);
	pthread_mutex_init(&(table->m_all_alive), NULL);
	pthread_mutex_init(&(table->m_state), NULL);
	pthread_mutex_init(&(table->m_nb_meals), NULL);
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
	init_global_mutex(table);
	return (init_table_bis(table, option, time));
}
