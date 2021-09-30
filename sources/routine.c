/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:53:25 by lle-briq          #+#    #+#             */
/*   Updated: 2021/09/30 19:10:46 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_state(t_philo *philo, int state)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&(table->display));
	if (philo->state != DEAD)
	{
		philo->state = state;
		if (state == EATING)
			gettimeofday(&(philo->last_meal), NULL);
	}
	pthread_mutex_unlock(&(table->display));

}

void	get_forks(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&(table->forks[philo->fork_left]));
	print_state(philo, 0);
	pthread_mutex_lock(&(table->forks[philo->fork_right]));
	print_state(philo, 0);
}

static int	start_eating(t_philo *philo)
{	
	update_state(philo, FORK);
	get_forks(philo, philo->table);
	update_state(philo, EATING);
	print_state(philo, 0);
	return (waiting(philo->table->option.time_eat, philo->table));
}

static int	start_sleeping(t_philo *philo)
{
	if (!philo->table->all_alive)
	 	return (STOP);
	update_state(philo, SLEEPING);
	print_state(philo, 0);
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
	print_state(philo, 0);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->id % 2 == 0)
		usleep(100);
	while (all_alive_or_hungry(philo->table) == CONTINUE)
		routine_loop(philo);
	return (NULL);
}
