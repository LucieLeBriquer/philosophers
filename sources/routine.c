/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:53:25 by lle-briq          #+#    #+#             */
/*   Updated: 2021/09/24 17:52:24 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forks(t_philo *philo, t_table *table)
{
	//print_breakpoint(philo, "start_get_forks");
	if (philo->fork_right == philo->fork_left)
	{
		philo->state = DEAD;
		table->all_alive = 0;
		return ;
	}
	//print_breakpoint(philo, "before forks mutex");
	pthread_mutex_lock(&(table->forks[philo->fork_left]));
	pthread_mutex_lock(&(table->forks[philo->fork_right]));
	if (!philo->table->all_alive)
		return ;
	//print_breakpoint(philo, "after forks mutex");
	philo->state = FORK;
	print_state(philo, 0);
	print_state(philo, 0);
	philo->state = EATING;
}

static int	start_eating(t_philo *philo)
{	
	//print_breakpoint(philo, "start_eating");
	if (!philo->table->all_alive)
		return (STOP);
	//print_breakpoint(philo, "before get_forks");
	get_forks(philo, philo->table);
	//print_breakpoint(philo, "after get_forks");
	gettimeofday(&(philo->last_meal), NULL);
	print_state(philo, 0);
	return (waiting(philo->table->option.time_eat, philo->table));
}

static int	start_sleeping(t_philo *philo)
{
	if (!philo->table->all_alive)
		return (STOP);
	philo->state = SLEEPING;
	print_state(philo, 0);
	return (waiting(philo->table->option.time_sleep, philo->table));
}

void	routine_loop(t_philo *philo)
{
	//print_breakpoint(philo, "first");
	if (!philo->table->all_alive || start_eating(philo) == STOP)
		return ;
	//print_breakpoint(philo, "forks ok");
	pthread_mutex_unlock(&(philo->table->forks[philo->fork_left]));
	pthread_mutex_unlock(&(philo->table->forks[philo->fork_right]));
	philo->nb_meals++;
	if (philo->nb_meals == philo->table->option.tot_meals)
	{
		philo->state = SLEEPING;
		print_state(philo, 0);
		return ;
	}
	if (!philo->table->all_alive || start_sleeping(philo) == STOP)
		return ;
	philo->state = THINKING;
	print_state(philo, 0);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (everybody_alive(philo->table) == CONTINUE
		&& philo->nb_meals != philo->table->option.tot_meals)
		routine_loop(philo);
	//print_state_philo(philo);
	return (NULL);
}
