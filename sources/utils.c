/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:53:25 by lle-briq          #+#    #+#             */
/*   Updated: 2021/09/24 17:38:44 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*get_state(int state)
{
	if (state == EATING)
		return ("eating");
	if (state == SLEEPING)
		return ("sleeping");
	if (state == THINKING)
		return ("thinking");
	if (state == FORK)
		return ("fork");
	else
		return ("dead");
}

void	print_state_philo(t_philo *philo)
{
	pthread_mutex_lock(&(philo->table->display));
	printf("PHILO %d at %ld\n\tState : %s\n\tStart time : %ld.%06ld\n", philo->id, get_time_stamp(philo->start_time), get_state(philo->state), philo->start_time.tv_sec, philo->start_time.tv_usec);
	printf("\tLast meal : %ld.%06ld\n\tNumber of meals : %d\n", philo->last_meal.tv_sec, philo->last_meal.tv_usec, philo->nb_meals);
	pthread_mutex_unlock(&(philo->table->display));
}

void	print_breakpoint(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&(philo->table->display));
	printf("Hello from philo %d [%s]\n", philo->id, msg);
	pthread_mutex_unlock(&(philo->table->display));
}
