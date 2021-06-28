/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucie <lucie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 20:10:42 by lucie             #+#    #+#             */
/*   Updated: 2021/06/28 20:50:59 by lucie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_option
{
	int		nb;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		tot_meals;
}			t_option;

typedef struct t_philo
{
	int			fork_left;
	int			fork_right;
	int			state;
	int			last_meal;
	int			nb_meals;
	pthread_t	thread;
	t_option	options; // useless si deja dans table ? a voir..
}				t_philo;

typedef struct s_table
{
	t_philo		*philo;
	t_option	option;
	//+ mutex pour chaque fourchette
}				t_table;


/*
**
*/

int	parse_option(t_option *option, int argc, char **argv);
int	print_help(void);
int	init_table(t_table *table, t_option option);

#endif