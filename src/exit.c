/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crocha-s <crocha-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:32:35 by crocha-s          #+#    #+#             */
/*   Updated: 2023/10/03 15:54:48 by crocha-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void clean_table(t_table *table)
{
	free(table->philo);
	free(table->fork_locker);
}

void destroy_lockers(t_table *table)
{
	int	i;
	
	i = -1;
	while(++i < table->philosophers)
		pthread_mutex_destroy(&table->fork_locker[i]);
	clean_table(table);
	pthread_mutex_destroy(&table->print_locker);
	pthread_mutex_destroy(&table->eat_locker);
	pthread_mutex_destroy(&table->finish_locker);
}

void finish_dinner(t_table *table)
{
	int	i;

	i = -1;

	while (i < table->philosophers)
		pthread_join(table->philo[i].thread, NULL);
	destroy_lockers(table);
	
}