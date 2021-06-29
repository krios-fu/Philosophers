/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:15:58 by krios-fu          #+#    #+#             */
/*   Updated: 2021/06/29 03:52:52 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	*start_philo(void *arg)
{
	t_philosophers *philo;
	t_philosophers *tmp_ph;

	philo = (t_philosophers *)arg;
	philo->time_to->tic_toc = (long long)(philo->time_to->die / 1000);
	philo->start_think = 0;
	if (philo->num % 2 == 0 || (philo->size_lst == (size_t)philo->num))
		usleep(philo->time_to->eat);
	if (philo->time_to->must_eat >= 1)
	{
		while (*philo->time_to->tmp_must_eat < philo->size_lst)
		{
			eat_philo(philo);
			if (*philo->time_to->tmp_must_eat == philo->size_lst)
				break ;
			sleep_philo(philo);
			if (*philo->time_to->tmp_must_eat == philo->size_lst)
				break ;
			think_philo(philo);
			if (*philo->time_to->tmp_must_eat == philo->size_lst)
				break ;
		}
	}
	else 
	{
		while (1)
		{
			eat_philo(philo);
			sleep_philo(philo);
			think_philo(philo);	
			if(philo->time_to->tic_toc < 0 || *philo->die == 1)
			{
				free_fork(philo);
				break;
			}
		}
		die_philo(philo);
	}
	return((void *)0);
}

void	create_philosophers(t_philosophers *lst_philos, int n_philo)
{
	t_philosophers	*tmp_ph;
	t_bool			die;
	int				i;
	int				j;

	j = n_philo -1 ;
	die = 0;
	tmp_ph = lst_philos;
	i = 0;
	while(i < n_philo)
	{
		lst_philos->hilo = (pthread_t *)malloc(sizeof(pthread_t));
		lst_philos->size_lst = n_philo;
		lst_philos->die = &die;
		pthread_mutex_init(&lst_philos->fork, NULL);
		pthread_create(lst_philos->hilo, NULL, start_philo, (void *)lst_philos);
		lst_philos = lst_philos->right;
		i++;
	}
	while(j >= 0)
	{
		pthread_join(*tmp_ph->hilo, NULL);
		tmp_ph = tmp_ph->right;
		j--;
	}
	 while(n_philo--)
	{
		pthread_mutex_destroy(&lst_philos->fork);
		if (lst_philos->right)
		{
			pthread_detach(*lst_philos->hilo);
			lst_philos = lst_philos->right;
			free(lst_philos->hilo);
			free(lst_philos->time_to);
			free(lst_philos);
		}
	}
}

int main (int argc, char *argv[])
{
	t_philosophers *lst_philo;
	struct timeval start;
	int n_philo;
	int i;

	if ((argc == 5 || argc == 6) && check_arg(argv) && min_atoi(argv[1]) > 1 && min_atoi(argv[5]) > 0)
	{
		n_philo = min_atoi(argv[1]);
		i = 2;
		gettimeofday(&start, NULL);
		lst_philo = new_philo(1, new_time(argv), start, n_philo);
		while (i <= n_philo)
		{
			add_philos(&lst_philo, new_philo(i, new_time(argv), start, n_philo));
			i++;
		}
		create_philosophers(lst_philo, n_philo);
	}
	else
		printf("philo: Error syntax arguments\n");
	return(0);
}