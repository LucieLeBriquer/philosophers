/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:53:56 by lle-briq          #+#    #+#             */
/*   Updated: 2021/11/22 18:11:44 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	free_all(t_table *table, int err)
{
	int	i;

	i = -1;
	while (++i < table->option.nb)
		pthread_mutex_destroy(&(table->forks[i]));
	pthread_mutex_destroy(&(table->m_display));
	pthread_mutex_destroy(&(table->m_all_alive));
	pthread_mutex_destroy(&(table->m_state));
	pthread_mutex_destroy(&(table->m_nb_meals));
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
	return (err);
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
			return (free_all(table, ERROR_THREAD));
	}
	while (all_alive_and_hungry(table) == CONTINUE)
		usleep(100);
	i = -1;
	while (++i < option.nb)
	{
		philo = table->philos + i;
		if (pthread_join(philo->thread, NULL))
			return (free_all(table, ERROR_THREAD));
	}
	return (free_all(table, SUCCESS));
}

static void	init_global_mutex(t_table *table)
{
	pthread_mutex_init(&(table->m_display), NULL);
	pthread_mutex_init(&(table->m_all_alive), NULL);
	pthread_mutex_init(&(table->m_state), NULL);
	pthread_mutex_init(&(table->m_nb_meals), NULL);
}

int	init_table(t_table *table, t_option option)
{
	int		i;
	t_time	time;

	if (gettimeofday(&time, NULL))
		return (ERROR_TIME);
	table->philos = malloc(sizeof(t_philo) * option.nb);
	table->forks = malloc(sizeof(t_mutex) * option.nb);
	table->option = option;
	table->all_alive = 1;
	if (!table->philos || !table->forks)
		return (free_all(table, ERROR_ALLOC));
	i = -1;
	while (++i < option.nb)
		pthread_mutex_init(&(table->forks[i]), NULL);
	init_global_mutex(table);
	return (init_table_bis(table, option, time));
}
