/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:16:29 by jbartosi          #+#    #+#             */
/*   Updated: 2023/03/17 16:32:44 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	do_sleep(t_philo **philo)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	printf("%-5lld %-5d \e[0;36m is sleeping \e[0m\n",
		timesince((*philo)->created_at, timenow), (*philo)->id);
	milisleep((*philo)->sleep);
}

void	do_think(t_philo **philo)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	printf("%-5lld %-5d \e[0;32m is thinking \e[0m\n",
		timesince((*philo)->created_at, timenow), (*philo)->id);
	milisleep((2 * (*philo)->eat) - (*philo)->sleep);
}
