/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:53:25 by lle-briq          #+#    #+#             */
/*   Updated: 2021/10/07 12:35:05 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forks(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&(table->forks[philo->fork_left]));
	print_state(philo);
	pthread_mutex_lock(&(table->forks[philo->fork_right]));
	print_state(philo);
}

static int	start_eating(t_philo *philo)
{	
	update_state(philo, FORK);
	get_forks(philo, philo->table);
	update_state(philo, EATING);
	print_state(philo);
	return (waiting(philo->table->option.time_eat, philo->table));
}

static int	start_sleeping(t_philo *philo)
{
	if (!philo->table->all_alive)
		return (STOP);
	update_state(philo, SLEEPING);
	print_state(philo);
	return (waiting(philo->table->option.time_sleep, philo->table));
}

void	routine_loop(t_philo *philo)
{
	if (start_eating(philo) == STOP)
		return ;
	pthread_mutex_unlock(&(philo->table->forks[philo->fork_left]));
	pthread_mutex_unlock(&(philo->table->forks[philo->fork_right]));
	philo->nb_meals++;
	if (start_sleeping(philo) == STOP)
		return ;
	update_state(philo, THINKING);
	print_state(philo);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (all_alive_and_hungry(philo->table) == CONTINUE)
		routine_loop(philo);
	return (NULL);
}
