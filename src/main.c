/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:28:05 by admin             #+#    #+#             */
/*   Updated: 2023/10/23 22:16:59 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int philosophers_into_threads(t_table *table)
{
    int i;

    i = -1;
    while(++i < table->philosophers)
    {
        if (pthread_create(&table->philo[i].thread, NULL, \
                start_dinner, &table->philo[i]))
                exit_error("Unable to create thread!", table, 3);
    }
    return (0);
}

void start_mutexes (t_table *table)
{
    int i;
    
    i = -1;
    while(++i < table->philosophers)
    {
        if(pthread_mutex_init(&table->fork_padlock[i],NULL))
            exit_error("Unable to start fork mutex.", table, 2);
    }
    if(pthread_mutex_init(&table->print_padlock,NULL))
        exit_error("Unable to init print mutex!", table, 2);
    if(pthread_mutex_init(&table->eat_padlock, NULL))
        exit_error("Unable to init eat mutex!", table, 2);
    if(pthread_mutex_init(&table->finish_padlock,2))
        exit_error("Unable to initiate finish mutex!",table, NULL);
}

void call_philosophers(t_table *table)
{
    int i;
    
    i = -1;
    table->philo = malloc(sizeof(t_philo) * table->philosophers);
    table->fork_padlock = malloc(sizeof(pthread_mutex_t) * table->philosophers);
    if (!table->philo || !table->fork_padlock )
        exit_error("Unable to create philosophers and forks", table, 1);
    table->start_time = now();
    while( ++i < table->philosophers)
    {
        table->philo[i].id = i + 1;
        table->philo[i].l_fork = i;
        table->philo[i].r_fork = (i + 1) % table->philosophers; // tentar sem "% table->..."
        table->philo[i].eat_count = 0;
        table->philo[i].last_eat = table->start_time;
        table->philo[i].table = table;
    }
}

void set_table(t_table *table, int ac, char **av)
{
    if (ac < 5 || ac > 6)
        exit_error("Wrong arguments number, should be 5 or 6 arguments!", NULL, 0);
    table->philosophers = ft_atoi(av[1]);
    table->time_to_die = ft_atoi(av[2]);
    table->time_to_eat = ft_atoi (av[3]);
    table->time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
        table->must_eat_times = ft_atoi(av[5]);
    else 
        table->must_eat_times = -1;
    if (table->philosophers < 1 || table->time_to_die < 1
        || table->time_to_eat < 1 || table->time_to_sleep < 1
        || (ac == 6 && table->must_eat_times < 1))
        exit_error("Invalid arguments", NULL, 0);
    table->finish_flag = 0;
}

void start_monitor (t_table *table)
{
    int i;
    int continue_flag;

    continue_flag = 1;
    while(continue_flag)
    {
        i = -1;
        table->ate_enough = 0;
        while (++i < table->philosophers)
        {
            if (continue_flag && is_someone_dead_or_full(&table->philo[i]))
                continue_flag = 0;
        }
        usleep(10);
    }
    finish_dinner(table);
}

int main(int ac, char**av)
{
    t_table table;
    
    set_table(&table, ac, av);
    call_philosophers(&table);
    start_mutexes(&table);
    philosophers_into_threads(&table);
    start_monitor(&table);
}