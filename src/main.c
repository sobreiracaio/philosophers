/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crocha-s <crocha-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:24:45 by crocha-s          #+#    #+#             */
/*   Updated: 2023/10/03 16:56:21 by crocha-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void set_table (t_table *table, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		exit_error("Invalid number of arguments");
	table->philosophers = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac ==6)
		table->times_must_eat = ft_atoi(av[5]);
	else
		table->times_must_eat = -1;
	if(table->philosophers < 1 || table->time_to_die < 1
	|| table->time_to_eat < 1 || table->time_to_sleep < 1
	|| (ac == 6 && table->times_must_eat < 1))
		exit_error("Invalid arguments", NULL, 0);
	table->finish_flag =0;
}

int main(int ac, char **av)
{
	t_table table;
	
	set_table(&table, ac, av);
	
}