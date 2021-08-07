/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucie <lucie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 20:10:42 by lucie             #+#    #+#             */
/*   Updated: 2021/08/07 09:35:53 by lucie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct timeval t_time;
typedef pthread_mutex_t t_mutex;

typedef struct s_option
{
	int		nb;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		tot_meals;
}			t_option;

typedef struct s_table
{
	t_mutex		display;
	t_mutex		*forks;
	int			*forks_free;
	t_option	option;
	int			all_alive;
}				t_table;

typedef struct t_philo
{
	int			id;
	int			fork_left;
	int			fork_right;
	int			state;
	int			nb_meals;
	t_table		*table;
	t_time		last_meal;
	t_time		start_time;
	pthread_t	thread;
}				t_philo;

enum    {EATING, SLEEPING, THINKING, DEAD};
enum	{FREE, UNAVAILABLE};
enum	{FORMAT = -2, SUCCESS = 0, ERROR_THREAD, ERROR_ALLOC, ERROR_TIME, ERROR_PARSE};

/*
** Utils
*/

int		parse_option(t_option *option, int argc, char **argv);
int		print_help(void);
int		init_table(t_table *table, t_philo *philo, t_option option);
long	get_time(void);

/*
** Routine
*/

void	*stupid_routine(void *param);
void	*routine(void *param);


#endif