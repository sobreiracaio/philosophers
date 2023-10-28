/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:27:22 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/10/28 20:51:37 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				l_fork;
	int				r_fork;
	long long		last_eat;
	struct s_table	*table;
	pthread_t		thread;
}					t_philo;

typedef struct s_table
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_times;
	int				ate_enough;
	int				finish_flag;
	long long		start_time;
	t_philo			*philo;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	finish_mutex;
}					t_table;

# define TAKE "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"
# define FINISH "f"
# define FINISH_MSG "All philosophers ate enough!"
# define YES 1
# define NO 0

void		emulate_action(t_philo *philo, long long ms);
void		print_action(t_philo *philo, const char *status);
long long	now(void);
void		exit_error(char *msg, t_table *table, int n);
int			ft_atoi(const char *s);

int			dinner_for_one(t_table *table);
void		start_mutexes(t_table *table);
void		call_philosophers(t_table *table);
void		set_table(t_table *table, int ac, char **av);

int			time_to_finish(t_philo *philo, int order);
int			dead_or_full(t_philo *philo);
void		time_to_eat(t_philo *philo);
void		*start_dinner(void *arg);
int			philos_into_threads(t_table *table);

void		clean_table(t_table *table);
void		destroy_mutexes(t_table *table);
void		finish_dinner(t_table *table);
void		start_monitor(t_table *table);

#endif