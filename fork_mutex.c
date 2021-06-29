/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 02:12:39 by krios-fu          #+#    #+#             */
/*   Updated: 2021/06/29 02:43:32 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void take_fork(t_philosophers *philo)
{

	pthread_mutex_lock(&philo->left->fork);
	if (philo->time_to->tic_toc <= 0 ||  *philo->die == 1)
		return ;
	print_status(philo, "\033[1;32mhas taken a fork");
	pthread_mutex_lock(&philo->fork);
	if (philo->time_to->tic_toc <= 0 ||  *philo->die == 1)
		return ;
	print_status(philo, "\033[1;32mhas taken a fork");
	if(get_time() - philo->start > ((philo->time_to->eat + 10000) / 1000))
	{
		if (philo->think == 1 || (philo->size_lst % 2) == 0)
		 	philo->time_to->tic_toc -= ((get_time() - philo->start) - philo->start_think) * 1000;
		philo->think = 1;
	}
	if (philo->time_to->tic_toc <= 0 || *philo->die == 1)
	{
		free_fork(philo);
		return ;
	}

}

void free_fork(t_philosophers *philo)
{
	pthread_mutex_unlock(&philo->left->fork);
	pthread_mutex_unlock(&philo->fork);
}