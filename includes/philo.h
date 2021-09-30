/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:54:04 by lle-briq          #+#    #+#             */
/*   Updated: 2021/09/30 18:58:24 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# define FORMAT -2
# define SUCCESS 0
# define ERROR_THREAD 1
# define ERROR_ALLOC 2
# define ERROR_TIME 3
# define ERROR_PARSE 4
# define EATING 5
# define SLEEPING 6
# define THINKING 7
# define FORK 8
# define DEAD 9
# define CONTINUE 10
# define STOP 11

typedef struct timeval	t_time;
typedef pthread_mutex_t	t_mutex;

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
	t_mutex				display;
	t_mutex				*forks;
	t_option			option;
	struct s_philo		*philos;
	int					all_alive;
}						t_table;

typedef struct s_philo
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

int		parse_option(t_option *option, int argc, char **argv);
int		print_help(void);
int		init_table(t_table *table, t_philo *philo, t_option option);
long	get_time(void);
long	get_time_stamp(t_time start);
void	print_state(t_philo *philo, int full);
int		waiting(long to_wait, t_table *table);
void	*routine(void *param);
int		everybody_alive(t_table *table);
void	update_state(t_philo *philo, int state);
int		all_alive_or_hungry(t_table *table);


/*
** Utils
*/

void	print_states(t_table *table, int i);
void	print_msg(char *s, int i, t_table *table);
void	print_philo_state(t_philo *philo, t_table *table);
void	print_table_state(t_table *table);

#endif
