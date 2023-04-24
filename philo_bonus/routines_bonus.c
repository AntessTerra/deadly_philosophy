/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:16:29 by jbartosi          #+#    #+#             */
/*   Updated: 2023/04/24 17:49:49 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	odd_sleep(t_philo **philo)
{
	struct timeval	timenow;

	if ((*philo)->init_sleep)
		gettimeofday(&(*philo)->ate_last, NULL);
	if ((*philo)->id % 2 == 0 && (*philo)->init_sleep)
	{
		gettimeofday(&timenow, NULL);
		if ((*philo)->alive[0])
			printf("%-5lld %-5d \e[0;36m is sleeping \e[0m\n",
				timesince((*philo)->created_at, timenow), (*philo)->id + 1);
		milisleep((*philo)->sleep);
		(*philo)->init_sleep = 0;
	}
}

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

void	grab_forks(t_philo **philo, sem_t *sem)
{
	struct timeval	timenow;

	sem_wait(sem);
	gettimeofday(&timenow, NULL);
	if ((*philo)->alive[0])
		printf("%-5lld %-5d \e[0;33m has taken a fork\e[0m\n",
			timesince((*philo)->created_at, timenow), (*philo)->id + 1);
	sem_wait(sem);
	gettimeofday(&timenow, NULL);
	if ((*philo)->alive[0])
		printf("%-5lld %-5d \e[0;33m has taken a fork\e[0m\n",
			timesince((*philo)->created_at, timenow), (*philo)->id + 1);
}

int	do_eat(t_philo **philo, sem_t *sem)
{
	struct timeval	timenow;

	grab_forks(philo, sem);
	if (!is_alive(philo))
		return (0);
	gettimeofday(&(*philo)->ate_last, NULL);
	gettimeofday(&timenow, NULL);
	if ((*philo)->alive[0])
		printf("%-5lld %-5d \e[0;35m is eating \e[0m\n",
			timesince((*philo)->created_at, timenow), (*philo)->id + 1);
	milisleep((*philo)->eat);
	sem_post(sem);
	sem_post(sem);
	(*philo)->n_ate++;
	return (1);
}
