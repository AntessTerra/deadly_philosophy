/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:16:29 by jbartosi          #+#    #+#             */
/*   Updated: 2023/04/25 14:22:21 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	abortion(t_philo *philos)
{
	int	n;

	n = -1;
	while (++n < philos[0].n_phil)
		kill(philos[0].pids[n], SIGKILL);
}

void	odd_sleep(t_philo **philo, sem_t *megaphone)
{
	struct timeval	timenow;

	if ((*philo)->init_sleep)
		gettimeofday(&(*philo)->ate_last, NULL);
	if ((*philo)->id % 2 == 0 && (*philo)->init_sleep)
	{
		gettimeofday(&timenow, NULL);
		sem_wait(megaphone);
		if ((*philo)->alive[0])
			printf("%-5lld %-5d \e[0;36m is sleeping \e[0m\n",
				timesince((*philo)->created_at, timenow), (*philo)->id + 1);
		sem_post(megaphone);
		milisleep((*philo)->sleep);
		gettimeofday(&timenow, NULL);
		sem_wait(megaphone);
		if ((*philo)->alive[0])
			printf("%-5lld %-5d \e[0;32m is thinking \e[0m\n",
				timesince((*philo)->created_at, timenow), (*philo)->id + 1);
		sem_post(megaphone);
		(*philo)->init_sleep = 0;
	}
}

void	do_sleep(t_philo **philo, sem_t *megaphone)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	sem_wait(megaphone);
	if ((*philo)->alive[0])
		printf("%-5lld %-5d \e[0;36m is sleeping \e[0m\n",
			timesince((*philo)->created_at, timenow), (*philo)->id + 1);
	sem_post(megaphone);
	milisleep((*philo)->sleep);
	gettimeofday(&timenow, NULL);
	sem_wait(megaphone);
	if ((*philo)->alive[0])
		printf("%-5lld %-5d \e[0;32m is thinking \e[0m\n",
			timesince((*philo)->created_at, timenow), (*philo)->id + 1);
	sem_post(megaphone);
	milisleep(1);
}

void	grab_forks(t_philo **philo, sem_t *sem, sem_t *megaphone)
{
	struct timeval	timenow;

	sem_wait(sem);
	gettimeofday(&timenow, NULL);
	sem_wait(megaphone);
	if ((*philo)->alive[0])
		printf("%-5lld %-5d \e[0;33m has taken a fork\e[0m\n",
			timesince((*philo)->created_at, timenow), (*philo)->id + 1);
	sem_post(megaphone);
	sem_wait(sem);
	gettimeofday(&timenow, NULL);
	sem_wait(megaphone);
	if ((*philo)->alive[0])
		printf("%-5lld %-5d \e[0;33m has taken a fork\e[0m\n",
			timesince((*philo)->created_at, timenow), (*philo)->id + 1);
	sem_post(megaphone);
}

int	do_eat(t_philo **philo, sem_t *sem, sem_t *megaphone)
{
	struct timeval	timenow;

	grab_forks(philo, sem, megaphone);
	if (!is_alive(philo, megaphone))
		return (0);
	gettimeofday(&(*philo)->ate_last, NULL);
	gettimeofday(&timenow, NULL);
	sem_wait(megaphone);
	if ((*philo)->alive[0])
		printf("%-5lld %-5d \e[0;35m is eating \e[0m\n",
			timesince((*philo)->created_at, timenow), (*philo)->id + 1);
	sem_post(megaphone);
	milisleep((*philo)->eat);
	sem_post(sem);
	sem_post(sem);
	(*philo)->n_ate++;
	return (1);
}
