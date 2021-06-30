/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 02:06:46 by krios-fu          #+#    #+#             */
/*   Updated: 2021/06/30 03:36:59 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	eat_philo(t_philosophers *philo)
{
	if (philo->time_to->tic_toc <= 0 || *philo->die == 1)
		return ;
	take_fork(philo);
	if (philo->time_to->tic_toc <= 0 || *philo->die == 1)
		return ;
	if (philo->time_to->must_eat)
		philo->time_to->count_eat++;
	print_status(philo, YELLOW"is eating");
	if (philo->time_to->count_eat == philo->time_to->must_eat)
		(*philo->time_to->tmp_must_eat)++;
	philo->time_to->tic_toc = (long long)(philo->time_to->die / 1000);
	if (philo->time_to->eat > philo->time_to->die)
		usleep(philo->time_to->die);
	else
		usleep(philo->time_to->eat);
	if (philo->time_to->must_eat == 0)
	{
		philo->time_to->tic_toc -= philo->time_to->eat / 1000;
		if (philo->time_to->tic_toc <= 0 || *philo->die == 1)
		{
			free_fork(philo);
			return ;
		}
	}
	free_fork(philo);
}

void	sleep_philo(t_philosophers *philo)
{
	if (philo->time_to->tic_toc <= 0 || *philo->die == 1)
		return ;
	print_status(philo, BLUE"is sleeping");
	if (philo->time_to->die < (philo->time_to->sleep + philo->time_to->eat))
		usleep(philo->time_to->die - philo->time_to->eat);
	else
		usleep(philo->time_to->sleep);
	if (philo->time_to->must_eat == 0)
		philo->time_to->tic_toc -= (long long)philo->time_to->sleep / 1000;
}

void	think_philo(t_philosophers *philo)
{
	// uint64_t	tmp_time;
	int			status;

	status = 0;
	if (*philo->die == 1)
		return ;
	print_status(philo, PINK"is thinking");
	while (status == 0)
	{
		// tmp_time = (get_time() - philo->start);
		if (philo->time_to->tic_toc <= 0 || *philo->die == 1)
		{
			// free_fork(philo);
			printf("sali\n");
			return ;
		}
		if (*philo->num_fork >= 2)
			status = 1;
		philo->start_think = (get_time() - philo->start);
		usleep(1500);
		philo->time_to->tic_toc
			-= ((get_time() - philo->start) - philo->start_think);
	}
}

void	die_philo(t_philosophers *philo)
{
	pthread_mutex_lock(philo->print_die);
	if (*philo->die == 0)
	{
		free_fork(philo);
		*philo->die = 1;
		printf(GRAY"%6llu %s \033[1;36m%3d  %s\n\033[1;37m",
			get_time() - philo->start, "ms", philo->num, RED"die");
	}
	pthread_mutex_unlock(philo->print_die);
}
