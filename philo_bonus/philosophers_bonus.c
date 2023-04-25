/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:55:45 by jbartosi          #+#    #+#             */
/*   Updated: 2023/04/25 14:51:20 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	freeee(t_philo *philos)
{
	sem_close(philos->forks);
	sem_close(philos->megaphone);
	free(philos->alive);
	free(philos->pids);
	free(philos);
}

int	is_alive(t_philo **philo, sem_t *megaphone)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	if (!(*philo)->alive[0])
		return (0);
	if (timesince((*philo)->ate_last, timenow) >= (*philo)->die)
	{
		sem_wait(megaphone);
		(*philo)->alive[0] = 0;
		printf("%-5lld %-5d \e[0;31m died \e[0m\n",
			timesince((*philo)->created_at, timenow), (*philo)->id + 1);
		return (0);
	}
	return (1);
}

void	*processs_routine(t_philo *philo)
{
	sem_t	*forks;
	sem_t	*megaphone;

	forks = sem_open(FORKS, 0);
	megaphone = sem_open(MEGAPHONE, 0);
	gettimeofday(&(*philo).ate_last, NULL);
	while (philo->alive[0])
	{
		odd_sleep(&philo, megaphone);
		if (!do_eat(&philo, forks, megaphone))
			return (sem_close(forks), sem_close(megaphone), NULL);
		if (philo->n_ate == philo->to_eat)
			return (sem_close(forks), sem_close(megaphone), NULL);
		do_sleep(&philo, megaphone);
	}
	return (sem_close(forks), sem_close(megaphone), NULL);
}

void	cutlery(t_philo *philos)
{
	int	n;

	n = -1;
	while (++n < philos[0].n_phil)
	{
		philos[n].id = n;
		philos[n].pids[n] = fork();
		if (philos[n].pids[n] == 0)
		{
			processs_routine(&philos[n]);
			freeee(philos);
			exit(2);
		}
		else if (philos[n].pids[n] < 0)
			perror("FAILED TO FORK IT UP\n");
	}
}

int	main(int argc, char **argv)
{
	t_philo	*philos;

	init_philo(argc, argv, &philos);
	if (philos[0].n_phil == 1)
	{
		milisleep(philos[0].sleep);
		printf("%-5d %-5s %-5s\n", philos[0].sleep, "1", "\e[0;31mhas died\e[0m");
		freeee(philos);
		exit(0);
	}
	sem_unlink(FORKS);
	philos->forks = sem_open(FORKS, O_CREAT, 0644, philos->n_phil);
	sem_unlink(MEGAPHONE);
	philos->megaphone = sem_open(MEGAPHONE, O_CREAT, 0644, 1);
	cutlery(philos);
	wait(NULL);
	abortion(philos);
	freeee(philos);
	return (0);
}
