/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crocha-s <crocha-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:26:58 by crocha-s          #+#    #+#             */
/*   Updated: 2023/10/03 15:40:09 by crocha-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void exit_error(char *msg, t_table *table, int error_nbr)
{
	printf("Error: %s", msg);
	if (error_nbr == 1)
		clean_table(table);
	if (error_nbr == 2)
		destroy_lockers(table);
	if (error_nbr == 3)
		finish_dinner(table);
	exit(1);
}