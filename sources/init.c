/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucie <lucie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 20:47:32 by lucie             #+#    #+#             */
/*   Updated: 2021/06/28 21:16:27 by lucie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*stupid_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	printf("i'm philo %d, my last meal was at %ld:%ld\n", philo->id, philo->last_meal.tv_sec, philo->last_meal.tv_usec);
	return (NULL);
}

static void	init_philosopher(t_philo *philo, int id, t_time time)
{
	philo->fork_left = -1;
	philo->fork_right = -1;
	philo->state = THINKING;
	philo->last_meal = time;
	philo->nb_meals = 0;
	philo->id = id + 1;
	pthread_create(&(philo->thread), NULL, &stupid_routine, philo); //TO PROTECT
}

int	init_table(t_table *table, t_option option)
{
	int		i;
	t_time	time;
	
	gettimeofday(&time, NULL);
	printf("%ld %ld\n", time.tv_sec, time.tv_usec);
	table->philo = malloc(option.nb * sizeof(t_philo));
	if (!table->philo)
		return (-1);
	i = -1;
	while (++i < option.nb)
		init_philosopher(&(table->philo[i]), i, time);
	i = -1;
	while (++i < option.nb)
		pthread_join(table->philo[i].thread, NULL);
	return (0);
}