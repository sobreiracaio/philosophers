/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:56:24 by admin             #+#    #+#             */
/*   Updated: 2023/10/17 18:05:53 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
    int id;
    int eat_count;
    int l_fork;
    int r_fork;
    long long last_eat;
    struct s_table *table;
    pthread_t   thread;
}   t_philo;

typedef struct s_table
{
    int philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat_times;
    int ate_enough;
    int finish_flag;
    long long start_time;
    t_philo *philo;
    pthread_mutex_t *fork_padlock;
    pthread_mutex_t print_padlock;
    pthread_mutex_t eat_padlock;
    pthread_mutex_t finish_padlock;
 }  t_table;





#endif