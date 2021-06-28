/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 02:06:46 by krios-fu          #+#    #+#             */
/*   Updated: 2021/06/28 03:18:46 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void eat_philo(t_philosophers *philo)
{
	take_fork(philo);
	if(philo->time_to->tic_toc > 0 && *philo->die == 0)
	{
		if (philo->time_to->must_eat)
			philo->time_to->count_eat++;
		print_status(philo, "\033[1;33mis eating");
		philo->time_to->tic_toc = philo->time_to->die;
		usleep(philo->time_to->eat);
		free_fork(philo);
		philo->time_to->tic_toc -= philo->time_to->eat;	
	}
}

void sleep_philo(t_philosophers *philo)
{
	if(philo->time_to->tic_toc > 0 && *philo->die == 0)
	{
		print_status(philo, "\033[1;34mis sleeping");
		usleep(philo->time_to->sleep);
		philo->time_to->tic_toc -= philo->time_to->sleep;
	}
}

void think_philo(t_philosophers *philo)
{
	if(philo->time_to->tic_toc > 0 && *philo->die == 0)
	{
		print_status(philo, "\033[1;35mis thinking");
		philo->start_think = (get_time() - philo->start);
	}
}

void	die_philo(t_philosophers *philo)
{
	pthread_mutex_lock(philo->print_die);
	if (*philo->die == 0)
	{
		*philo->die = 1;
		printf("%6llu %s \033[1;36m%3d  %s\n\033[1;37m",
			get_time() - philo->start, "ms",philo->num, "\033[1;31mis die");
	}
	pthread_mutex_unlock(philo->print_die);

}