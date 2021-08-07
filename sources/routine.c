/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucie <lucie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 17:39:17 by lucie             #+#    #+#             */
/*   Updated: 2021/08/07 09:38:07 by lucie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	t_time	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long int	get_time_stamp(t_time start)
{
	long	t;
	long	s;
	
	t = get_time();
	s = start.tv_sec * 1000 + start.tv_usec / 1000;
	return (t - s);
}

void	waiting(long to_wait)
{
	int	i;
	
	/*long int	current;

	current = get_time();
	printf("%ld %ld (%ld)\n", current, current + to_wait, to_wait);
	while (get_time() < current + to_wait)	// + pas de morts
		usleep(100);*/
	i = -1;
	while (++i < to_wait)
		usleep(1000);
}

void	get_forks(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&(table->forks[philo->fork_left]));
	pthread_mutex_lock(&(table->forks[philo->fork_right]));
	printf("%ld: %d has taken a fork\n", get_time_stamp(philo->start_time), philo->id);
	printf("%ld: %d has taken a fork\n", get_time_stamp(philo->start_time), philo->id);
	philo->state = EATING;
}

int	check_dead(t_philo *philo)	// il faut rajouter dans les conditions de fin que dès qu'un philo meure tout s'arrête
{
	if (get_time_stamp(philo->last_meal) > philo->table->option.time_die || !philo->table->all_alive)
	{
		philo->state = DEAD;
		if (philo->table->all_alive)
			printf("%ld: %d is dead\n", get_time_stamp(philo->start_time), philo->id);
		philo->table->all_alive = 0;
		return (1);
	}
	return (0);
}

void	routine_loop(t_philo *philo, t_table *table)
{
	// GRAB_FORKS
	get_forks(philo, table);
	// START_EATING
	gettimeofday(&(philo->last_meal), NULL);
	if (check_dead(philo))
		return ;
	printf("%ld: %d start eating\n", get_time_stamp(philo->start_time), philo->id);
	waiting(table->option.time_eat);
	pthread_mutex_unlock(&(table->forks[philo->fork_left]));
	table->forks_free[philo->fork_left] = FREE;
	pthread_mutex_unlock(&(table->forks[philo->fork_right]));
	table->forks_free[philo->fork_right] = FREE;
	if (check_dead(philo))
		return ;
	printf("%ld: %d done eating\n", get_time_stamp(philo->start_time), philo->id);
	philo->nb_meals++;
	if (philo->nb_meals == table->option.tot_meals)
		return ;
	philo->state = SLEEPING;
	// START_SLEEPING
	if (check_dead(philo))
		return ;
	printf("%ld: %d start sleeping\n", get_time_stamp(philo->start_time), philo->id);
	waiting(table->option.time_sleep);
	if (check_dead(philo))
		return ;
	printf("%ld: %d done sleeping\n", get_time_stamp(philo->start_time), philo->id);
	if (check_dead(philo))
		return ;
	philo->state = THINKING;
}

void	*routine(void *param)
{
	t_philo	*philo;
	t_table	*table;
	
	philo = (t_philo *)param;
	table = philo->table;
	while (philo->state != DEAD && philo->nb_meals != table->option.tot_meals)
		routine_loop(philo, table);
	return (NULL);
}