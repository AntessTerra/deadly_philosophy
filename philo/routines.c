/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:16:29 by jbartosi          #+#    #+#             */
/*   Updated: 2023/04/24 14:58:30 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	do_sleep(t_philo **philo)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	pthread_mutex_lock((*philo)->megaphone);
	if ((*philo)->alive[0])
		printf("%-5lld %-5d \e[0;36m is sleeping \e[0m\n",
			timesince((*philo)->created_at, timenow), (*philo)->id + 1);
	pthread_mutex_unlock((*philo)->megaphone);
	usleep((*philo)->sleep * 1000);
	gettimeofday(&timenow, NULL);
	pthread_mutex_lock((*philo)->megaphone);
	if ((*philo)->alive[0])
		printf("%-5lld %-5d \e[0;32m is thinking \e[0m\n",
			timesince((*philo)->created_at, timenow), (*philo)->id + 1);
	pthread_mutex_unlock((*philo)->megaphone);
}

void	fork_msg(t_philo **philo)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	pthread_mutex_lock((*philo)->megaphone);
	if ((*philo)->alive[0])
		printf("%-5lld %-5d \e[0;33m has taken a fork\e[0m\n",
			timesince((*philo)->created_at, timenow), (*philo)->id + 1);
	pthread_mutex_unlock((*philo)->megaphone);
}

void	grab_forks(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->mutexes[(*philo)->id]);
	(*philo)->forks[(*philo)->id] = 0;
	fork_msg(philo);
	if ((*philo)->id == (*philo)->n_phil - 1)
	{
		pthread_mutex_lock(&(*philo)->mutexes[0]);
		(*philo)->forks[0] = 0;
		fork_msg(philo);
	}
	else
	{
		pthread_mutex_lock(&(*philo)->mutexes[(*philo)->id + 1]);
		(*philo)->forks[(*philo)->id + 1] = 0;
		fork_msg(philo);
	}
}

void	letgo_forks(t_philo **philo)
{
	pthread_mutex_unlock(&(*philo)->mutexes[(*philo)->id]);
	(*philo)->forks[(*philo)->id] = 1;
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

int	do_eat(t_philo **philo)
{
	struct timeval	timenow;

	grab_forks(philo);
	if (!is_alive(philo))
		return (letgo_forks(philo), 0);
	gettimeofday(&(*philo)->ate_last, NULL);
	gettimeofday(&timenow, NULL);
	pthread_mutex_lock((*philo)->megaphone);
	if ((*philo)->alive[0])
		printf("%-5lld %-5d \e[0;35m is eating \e[0m\n",
			timesince((*philo)->created_at, timenow), (*philo)->id + 1);
	pthread_mutex_unlock((*philo)->megaphone);
	usleep((*philo)->eat * 1000);
	letgo_forks(philo);
	(*philo)->n_ate++;
	return (1);
}
