/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crocha-s <crocha-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:14:30 by crocha-s          #+#    #+#             */
/*   Updated: 2023/10/03 15:24:30 by crocha-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int	id;
	int	eat_count;
	int	l_fork;
	int r_fork;
	struct s_table	*table;
	pthread_t	thread;
}	t_philo;

typedef struct s_table
{
	int	philosophers;
	int	time_to_die;
	int time_to_eat;
	int	time_to_die;
	int	times_must_eat;
	int	is_full;
	int	finish_flag;
	long long	start_time;
	t_philo	*philo;
	pthread_mutex_t *fork_locker;
	pthread_mutex_t print_locker;
	pthread_mutex_t eat_locker;
	pthread_mutex_t finish_locker;

}	t_table;

#endif