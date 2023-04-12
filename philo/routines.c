/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:16:29 by jbartosi          #+#    #+#             */
/*   Updated: 2023/04/12 18:35:37 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	do_sleep(t_philo **philo)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	if ((*philo)->alive[0])
		printf("%-5lld %-5d \e[0;36m is sleeping \e[0m\n",
			timesince((*philo)->created_at, timenow), (*philo)->id + 1);
	milisleep((*philo)->sleep);
}

void	do_think(t_philo **philo)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	if ((*philo)->alive[0])
		printf("%-5lld %-5d \e[0;32m is thinking \e[0m\n",
			timesince((*philo)->created_at, timenow), (*philo)->id + 1);
	milisleep((2 * (*philo)->eat) - (*philo)->sleep);
}

void	grab_forks(t_philo **philo)
{
	struct timeval	timenow;

	pthread_mutex_lock(&(*philo)->mutexes[(*philo)->id]);
	(*philo)->forks[(*philo)->id] = 0;
	gettimeofday(&timenow, NULL);
	printf("%-5lld %-5d \e[0;33m has taken a fork\e[0m\n",
		timesince((*philo)->created_at, timenow), (*philo)->id + 1);
	if ((*philo)->id == (*philo)->n_phil - 1)
	{
		pthread_mutex_lock(&(*philo)->mutexes[0]);
		(*philo)->forks[0] = 0;
		gettimeofday(&timenow, NULL);
		printf("%-5lld %-5d \e[0;33m has taken a fork\e[0m\n",
			timesince((*philo)->created_at, timenow), (*philo)->id + 1);
	}
	else
	{
		pthread_mutex_lock(&(*philo)->mutexes[(*philo)->id + 1]);
		(*philo)->forks[(*philo)->id + 1] = 0;
		gettimeofday(&timenow, NULL);
		printf("%-5lld %-5d \e[0;33m has taken a fork\e[0m\n",
			timesince((*philo)->created_at, timenow), (*philo)->id + 1);
	}
}

void	letgo_forks(t_philo **philo)
{
	struct timeval	timenow;

	pthread_mutex_unlock(&(*philo)->mutexes[(*philo)->id]);
	(*philo)->forks[(*philo)->id] = 1;
	gettimeofday(&timenow, NULL);
	if ((*philo)->id == (*philo)->n_phil - 1)
	{
		pthread_mutex_unlock(&(*philo)->mutexes[0]);
		(*philo)->forks[0] = 1;
	}
	else
	{
		pthread_mutex_unlock(&(*philo)->mutexes[(*philo)->id + 1]);
		(*philo)->forks[(*philo)->id + 1] = 1;
	}
}

void	do_eat(t_philo **philo)
{
	struct timeval	timenow;

	if (!is_alive(philo))
		return ((void) 0);
	grab_forks(philo);
	gettimeofday(&timenow, NULL);
	printf("%-5lld %-5d \e[0;35m is eating \e[0m\n",
		timesince((*philo)->created_at, timenow), (*philo)->id + 1);
	milisleep((*philo)->eat);
	letgo_forks(philo);
	(*philo)->n_ate++;
}
