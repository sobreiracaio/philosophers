/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:00:04 by admin             #+#    #+#             */
/*   Updated: 2023/10/17 19:33:35 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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