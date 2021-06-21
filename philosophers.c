/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:15:58 by krios-fu          #+#    #+#             */
/*   Updated: 2021/06/21 23:04:27 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void eat_philo(pthread_mutex_t *status, void *arg)
{
	int i = 0;
	pthread_mutex_lock(status);

	while (i < 5)
	{
		printf("Hilo %i\n", (int)arg);
		i++;
	}
	pthread_mutex_unlock(status);
	
}
void	*philo(void *arg)
{
	pthread_mutex_t status;
	int i;
	i = 0;
	while(i < 10)
	{
		eat_philo(&status, arg);
		sleep(2);
		i++;
	}
	return(arg);
	
}

int main(int argc, char *argv[])
{

	printf("%d", min_atoi("1234546789"));
	// pthread_t hilo[2];
	// int i = 1;

	// pthread_create(&hilo[0], NULL, philo, (void*)1);
	// pthread_create(&hilo[1], NULL, philo, (void*)2);
	// pthread_join(hilo[0], NULL);
	// pthread_join(hilo[1], NULL);
	
	return (0);
}