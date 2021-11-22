/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:41:59 by lle-briq          #+#    #+#             */
/*   Updated: 2021/11/22 17:41:59 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philosophers(t_table *table, t_time time)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->option.nb)
	{
		philo = &(table->philos[i]);
		philo->fork_left = i;
		philo->fork_right = i + 1;
		if (i + 1 == table->option.nb)
		{
			philo->fork_left = 0;
			philo->fork_right = i;
		}
		philo->state = THINKING;
		philo->last_meal = time;
		philo->start_time = time;
		philo->nb_meals = 0;
		philo->id = i + 1;
		philo->table = table;
	}
}

int	everyone_is_full(t_table *table)
{
	int	i;
	int	tot_meals;
	int	philo_meals;

	i = -1;
	tot_meals = table->option.tot_meals;
	while (++i < table->option.nb)
	{
		pthread_mutex_lock(&(table->m_nb_meals));
		philo_meals = table->philos[i].nb_meals;
		pthread_mutex_unlock(&(table->m_nb_meals));
		if (philo_meals < tot_meals || tot_meals == -1)
			return (0);
	}
	return (1);
}

int	everybody_alive(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->option.nb)
	{
		philo = table->philos + i;
		if (get_time_stamp(philo->last_meal) > table->option.time_die)
		{
			pthread_mutex_lock(&(table->m_state));
			philo->state = DEAD;
			pthread_mutex_unlock(&(table->m_state));
			pthread_mutex_lock(&(table->m_all_alive));
			table->all_alive = 0;
			pthread_mutex_unlock(&(table->m_all_alive));
			print_state(philo);
			return (STOP);
		}
	}
	return (CONTINUE);
}

int	all_alive_and_hungry(t_table *table)
{
	if (everybody_alive(table) == STOP)
		return (STOP);
	if (everyone_is_full(table) == 1)
		return (STOP);
	return (CONTINUE);
}
