/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:56:44 by jbartosi          #+#    #+#             */
/*   Updated: 2023/04/13 15:49:31 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_philo
{
	int				id;
	int				eat;
	int				die;
	int				sleep;
	int				to_eat;
	int				n_phil;
	int				n_ate;
	int				*alive;
	int				init_sleep;
	int				*forks;
	struct timeval	created_at;
	struct timeval	ate_last;
	pthread_t		thread;
	pthread_mutex_t	*mutexes;
}				t_philo;

long long	timesince(struct timeval then, struct timeval now);
void		milisleep(int microsec);
void		init_philo(int argc, char **argv, t_philo **philos,
				pthread_mutex_t **mutexes);
void		do_think(t_philo **philo);
void		do_sleep(t_philo **philo);
void		do_eat(t_philo **philo);
int			is_alive(t_philo **philo);

#endif
