/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:46:42 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/10/30 19:26:36 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	clean_table(t_table *table)
{
	free (table->philo);
	free (table->fork_mutex);
}

void	destroy_mutexes(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philos)
		pthread_mutex_destroy(&table->fork_mutex[i]);
	clean_table(table);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->eat_mutex);
	pthread_mutex_destroy(&table->finish_mutex);
}

void	finish_dinner(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philos)
		pthread_join(table->philo[i].thread, NULL);
	destroy_mutexes(table);
}

void	start_monitor(t_table *table)
{
	int	i;
	int	continue_flag;

	continue_flag = 1;
	while (continue_flag)
	{
		i = -1;
		table->ate_enough = 0;
		while (++i < table->n_philos)
		{
			if (continue_flag && dead_or_full(&table->philo[i]))
				continue_flag = 0;
		}
		usleep(10);
	}
	finish_dinner(table);
}
