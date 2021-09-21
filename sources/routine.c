/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:53:25 by lle-briq          #+#    #+#             */
/*   Updated: 2021/09/21 20:09:32 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forks(t_philo *philo, t_table *table)
{
	if (philo->fork_right == philo->fork_left)
	{
		philo->state = DEAD;
		table->all_alive = 0;
		return ;
	}
	pthread_mutex_lock(&(table->forks[philo->fork_left]));
	pthread_mutex_lock(&(table->forks[philo->fork_right]));
	philo->state = FORK;
	print_state(philo, 0);
	print_state(philo, 0);
	philo->state = EATING;
}

static int	start_eating(t_philo *philo)
{
	if (check_dead(philo))
		return (STOP);
	get_forks(philo, philo->table);
	//pthread_mutex_lock(&(philo->table->display));
	//printf(">> changing time of last meal %ld for philo %d time_die[%d]\n", get_time_stamp(philo->last_meal), philo->id, philo->table->option.time_die);
	//pthread_mutex_unlock(&(philo->table->display));
	gettimeofday(&(philo->last_meal), NULL);
	print_state(philo, 0);
	waiting(philo->table->option.time_eat, philo->table);
	return (CONTINUE);
}

static int	start_sleeping(t_philo *philo)
{
	if (check_dead(philo))
		return (STOP);
	philo->state = SLEEPING;
	print_state(philo, 0);
	waiting(philo->table->option.time_sleep, philo->table);
	return (CONTINUE);
}

void	routine_loop(t_philo *philo)
{
	if (start_eating(philo) == STOP)
		return ;
	pthread_mutex_unlock(&(philo->table->forks[philo->fork_left]));
	pthread_mutex_unlock(&(philo->table->forks[philo->fork_right]));
	philo->nb_meals++;
	if (philo->nb_meals == philo->table->option.tot_meals)
	{
		philo->state = SLEEPING;
		print_state(philo, 0);
		return ;
	}
	if (start_sleeping(philo) == STOP)
		return ;
	if (check_dead(philo))
		return ;
	philo->state = THINKING;
	print_state(philo, 0);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (philo->state != DEAD
		&& philo->nb_meals != philo->table->option.tot_meals)
		routine_loop(philo);
	return (NULL);
}
