/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:56:44 by jbartosi          #+#    #+#             */
/*   Updated: 2023/04/25 14:22:31 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <signal.h>

# define FORKS "/SEM_FORKS"
# define MEGAPHONE "/SEM_MEGAPHONE"

typedef struct s_philo
{
	int				id;
	int				eat;
	int				die;
	int				sleep;
	int				to_eat;
	int				n_phil;
	int				n_ate;
	sem_t			*forks;
	sem_t			*megaphone;
	pid_t			*pids;
	int				*alive;
	int				init_sleep;
	struct timeval	created_at;
	struct timeval	ate_last;
}				t_philo;

long long	timesince(struct timeval then, struct timeval now);
void		milisleep(int microsec);
void		init_philo(int argc, char **argv, t_philo **philos);
void		do_sleep(t_philo **philo, sem_t *megaphone);
int			do_eat(t_philo **philo, sem_t *forks, sem_t *megaphone);
void		odd_sleep(t_philo **philo, sem_t *megaphone);
int			is_alive(t_philo **philo, sem_t *megaphone);
void		abortion(t_philo *philos);

#endif
