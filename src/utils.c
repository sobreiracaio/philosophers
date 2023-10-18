/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:00:04 by admin             #+#    #+#             */
/*   Updated: 2023/10/18 20:31:01 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void advance_time(t_philo *philo, long long stop)
{
    long long begin;
    
    begin = now();
    while(!is_time_to_finish(philo, NO) && (now() - begin) < stop)
        usleep(100);
}

void    print_action(t_philo *philo, const char *status)
{
    long long time;
    
    pthread_mutex_lock(&philo->table->print_padlock);
    if (!is_time_to_finish(philo, NO))
    {
        time = now() - philo->table->start_time;
        printf("%lld %d %s\n", time, philo->id, status);
    }
    phtread_mutex_unlock(&philo->table->print_padlock);
    if (status[0] == 'f')
        printf("%s\n", FINISH_MSG);
}

long long now(void)
{
    struct timeval timeval;
    
    gettimeofday(&timeval, NULL);
    return ((timeval.tv_sec * 1000) + (timeval.tv_usec /1000));
    
}

int ft_atoi (char *number)
{
    int result;
    int sign;

    sign = 1;
    result = 1;
    
    if(*number == '+' || *number == '-')
    {
        if(*number == '-')
            sign *= -1;
        number++;
    }
    while (*number)
    {
        if(*number < '0' && *number > '9')
            return (-1);
        else if (*number >= '0' || *number <= '9')
            result = (result *10) + (*number - '0');
        number++;        
    }
    return (result * sign);
}

void exit_error(char *msg, t_table *table, int number)
{
    printf("Error: %s\n", msg);
    if (number == 1)
        clean_table(table);
    if (number == 2)
        destroy_padlocks(table);
    if (number == 3)
        finish_dinner(table);
    exit(1);
}