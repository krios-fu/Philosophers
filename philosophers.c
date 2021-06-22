/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:15:58 by krios-fu          #+#    #+#             */
/*   Updated: 2021/06/22 22:43:58 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void eat_philo(pthread_mutex_t *status, int n_philo)
{
	pthread_mutex_lock(status);
		printf("Hilo %i\n", n_philo);
	pthread_mutex_unlock(status);
	//sleep(2);
	
}
void	*start_philo(void *arg)
{
	static pthread_mutex_t status;
	
	pthread_mutex_init(&status, NULL);
	eat_philo(&status, *((int*)arg));
	return(arg);	
}

void	create_philosophers(pthread_t *philo, int n_philo)
{
	int i, j;

	i = 0;
	j = n_philo -1 ;
	pthread_mutex_t status;

	pthread_mutex_init(&status, NULL);
	while(i < n_philo)
	{
		pthread_create(&philo[i], NULL, start_philo, &i );
		i++;
	}

	while(j >= 0)
	{
		pthread_join(philo[j], NULL);
		j--;
	}
	
}

int main(int argc, char *argv[])
{
	(void)argc;
	int n_philo;
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