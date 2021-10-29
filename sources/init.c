/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:53:56 by lle-briq          #+#    #+#             */
/*   Updated: 2021/10/29 18:43:59 by lle-briq         ###   ########.fr       */
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
	int	i;

	i = -1;
	while (++i < table->option.nb)
		pthread_mutex_destroy(&(table->forks[i]));
	pthread_mutex_destroy(&(table->display));
	if (table->philos)
		free(table->philos);
	if (table->forks)
		free(table->forks);
	return (ERROR_ALLOC);
}

int	all_alive_and_hungry(t_table *table)
{
	int	i;
	int	ok;

	if (everybody_alive(table) == STOP)
		return (STOP);
	pthread_mutex_lock(&(table->display));	
	ok = 0;
	i = -1;
	while (++i < table->option.nb)
		if (table->philos[i].nb_meals >= table->option.tot_meals
			&& table->option.tot_meals != -1)
			ok++;
	pthread_mutex_unlock(&(table->display));
	if (ok == table->option.nb)
		return (STOP);
	return (CONTINUE);
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
		philo = &(table->philos[i]);
		if (pthread_join(philo->thread, NULL))
			return (ERROR_THREAD);
		printf("thread %d has ended\n", i);
	}
	free_all(table);
	return (SUCCESS);
}

//TO DELETE
void	print_addresses(t_table *table)
{
	printf("&table %p\n", table);
	printf("&table->all_alive %p\n", &(table->all_alive));
	printf("&table->philos %p\n", &(table->philos));
	printf("&table->forks %p\n", &(table->forks));
	printf("&table->option %p\n", &(table->option));
	int	i = -1;
	while (++i < table->option.nb)
	{
		printf("&table->philos[%d] %p\n", i, &(table->philos[i]));
		printf("    &philos[%d]->id %p\n", i, &(table->philos[i].id));
		printf("    &philos[%d]->fl %p\n", i, &(table->philos[i].fork_left));
		printf("    &philos[%d]->fr %p\n", i, &(table->philos[i].fork_right));
		printf("    &philos[%d]->state %p\n", i, &(table->philos[i].state));
		printf("    &philos[%d]->nb_meals %p\n", i, &(table->philos[i].nb_meals));
	}
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
	//print_addresses(table);
	if (!philo || !table->forks)
		return (free_all(table));
	i = -1;
	while (++i < option.nb)
		pthread_mutex_init(&(table->forks[i]), NULL);
	pthread_mutex_init(&(table->display), NULL);
	return (init_table_bis(table, option, time));
}
