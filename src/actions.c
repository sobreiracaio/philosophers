/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:51:37 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/10/28 21:02:23 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	time_to_finish(t_philo *philo, int finish_order)
{
	pthread_mutex_lock(&philo->table->finish_mutex);
	if (finish_order || philo->table->finish_flag)
	{
		if (finish_order)
			philo->table->finish_flag = 1;
		pthread_mutex_unlock(&philo->table->finish_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->finish_mutex);
	return (0);
}

int	dead_or_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->eat_mutex);
	if (now() - philo->last_eat >= philo->table->time_to_die)
	{
		print_action(philo, DIE);
		time_to_finish(philo, YES);
		pthread_mutex_unlock(&philo->table->eat_mutex);
		return (1);
	}
	else if (philo->table->must_eat_times > 0
		&& philo->eat_count >= philo->table->must_eat_times)
	{
		philo->table->ate_enough++;
		if (philo->table->ate_enough >= philo->table->n_philos)
		{
			time_to_finish(philo, YES);
			print_action(philo, FINISH);
			pthread_mutex_unlock(&philo->table->eat_mutex);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->table->eat_mutex);
	return (0);
}

void	time_to_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->fork_mutex[philo->l_fork]);
		pthread_mutex_lock(&philo->table->fork_mutex[philo->r_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->table->fork_mutex[philo->r_fork]);
		pthread_mutex_lock(&philo->table->fork_mutex[philo->l_fork]);
	}
	print_action(philo, TAKE);
	print_action(philo, TAKE);
	print_action(philo, EAT);
	emulate_action(philo, philo->table->time_to_eat);
	pthread_mutex_lock(&philo->table->eat_mutex);
	philo->eat_count++;
	philo->last_eat = now();
	pthread_mutex_unlock(&philo->table->eat_mutex);
	pthread_mutex_unlock(&philo->table->fork_mutex[philo->r_fork]);
	pthread_mutex_unlock(&philo->table->fork_mutex[philo->l_fork]);
}

int	dinner_for_one(t_table *table)
{
	print_action(&table->philo[0], TAKE);
	emulate_action(&table->philo[0], table->time_to_die);
	print_action(&table->philo[0], DIE);
	time_to_finish(&table->philo[0], YES);
	return (0);
}

void	*start_dinner(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		usleep(philo->table->time_to_eat * 1000);
	while (1)
	{
		if (philo->table->n_philos == 1)
		{
			dinner_for_one(philo->table);
			return (0);
		}
		if (time_to_finish(philo, NO))
			return (0);
		time_to_eat(philo);
		print_action(philo, SLEEP);
		emulate_action(philo, philo->table->time_to_sleep);
		print_action(philo, THINK);
		if (philo->table->n_philos % 2 != 0
			&& philo->table->n_philos <= 127)
			emulate_action(philo, philo->table->time_to_eat);
	}	
	return (0);
}
