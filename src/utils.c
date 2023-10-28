/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:44:04 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/10/28 20:59:07 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	emulate_action(t_philo *philo, long long stop)
{
	long long	begin;

	begin = now();
	while (!time_to_finish(philo, NO) && (now() - begin) < stop)
		usleep(100);
}

void	print_action(t_philo *philo, const char *status)
{
	long long	time;

	pthread_mutex_lock(&philo->table->print_mutex);
	if (!time_to_finish(philo, NO))
	{
		time = now() - philo->table->start_time;
		printf("%lld %d %s\n", time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->table->print_mutex);
	if (status[0] == 'f')
		printf("%s\n", FINISH_MSG);
}

long long	now(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

void	exit_error(char *msg, t_table *table, int n)
{
	printf("Error: %s\n", msg);
	if (n == 1)
		clean_table(table);
	if (n == 2)
		destroy_mutexes(table);
	if (n == 3)
		finish_dinner(table);
	exit(1);
}

int	ft_atoi(const char *s)
{
	int	r;
	int	sg;

	r = 0;
	sg = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sg *= -1;
		s++;
	}
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (-1);
		else if (*s >= '0' && *s <= '9')
			r = (r * 10) + (*s - '0');
		s++;
	}
	return (sg * r);
}
