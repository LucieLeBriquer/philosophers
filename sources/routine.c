/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:53:25 by lle-briq          #+#    #+#             */
/*   Updated: 2021/10/27 19:09:13 by lle-briq         ###   ########.fr       */
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
{;
	if (!everybody_alive(philo->table))
		return (STOP);
	update_state(philo, SLEEPING);
	print_state(philo);
	return (waiting(philo->table->option.time_sleep, philo->table));
}

static void	routine_one(t_philo *philo)
{
	update_state(philo, FORK);
	pthread_mutex_lock(&(philo->table->forks[philo->fork_left]));
	print_state(philo);
	waiting(philo->table->option.time_die, philo->table);
	update_state(philo, DEAD);
	pthread_mutex_unlock(&(philo->table->forks[philo->fork_left]));
}

void	routine_loop(t_philo *philo)
{
	if (philo->fork_left == philo->fork_right)
	{
		routine_one(philo);
		return ;
	}
	if (start_eating(philo) == STOP)
	{
		pthread_mutex_unlock(&(philo->table->forks[philo->fork_left]));
		pthread_mutex_unlock(&(philo->table->forks[philo->fork_right]));
		return ;
	}
	pthread_mutex_unlock(&(philo->table->forks[philo->fork_left]));
	pthread_mutex_unlock(&(philo->table->forks[philo->fork_right]));
	pthread_mutex_lock(&(philo->table->m_nb_meals));
	philo->nb_meals++;
	pthread_mutex_unlock(&(philo->table->m_nb_meals));
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
		usleep(500);
	while (1)
	{
		if (all_alive_and_hungry(philo->table) == STOP)
			break ;
		routine_loop(philo);
	}
	return (NULL);
}
