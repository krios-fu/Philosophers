/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:15:58 by krios-fu          #+#    #+#             */
/*   Updated: 2021/06/22 02:47:15 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void eat_philo(pthread_mutex_t *status, long n_philo)
{
	int i = 0;
	pthread_mutex_lock(status);

	while (i < 5)
	{
		printf("Hilo %li\n", n_philo);
		i++;
	}
	pthread_mutex_unlock(status);
	
}
void	*start_philo(void *arg)
{
	pthread_mutex_t status;
	int i;
	i = 0;
	// while(i < 10)
	// {
		eat_philo(&status, (long)arg);
		sleep(3);
		i++;
	// }
	return(arg);
	
}

void	create_philosophers(pthread_t *philo, long n_philo)
{
	int i;

	i = 0;

	while(i < n_philo)
	{
		pthread_create(&philo[i], NULL, start_philo, (void *)i + 1);

		i++;
	}

	i = 0;
	while(i < n_philo)
	{
		pthread_join(philo[i], NULL);
		i++;
		
	}
	
	
}

int main(int argc, char *argv[])
{
	(void)argc;
	long n_philo;
	pthread_t *philo;

	n_philo = min_atoi(argv[1]);
	if (n_philo > 0)
	{
		philo = (pthread_t *)malloc(sizeof(pthread_t) * n_philo);
		if (!philo)
			printf("Error:\nMalloc");
	}
	else
		{
			printf("Error:\nInvalid argument: %s\n", argv[1]);
			return(-1);
		}
	create_philosophers(philo, n_philo);
	
	return (0);
}