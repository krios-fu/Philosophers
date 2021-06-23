/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:15:58 by krios-fu          #+#    #+#             */
/*   Updated: 2021/06/23 23:31:38 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void eat_philo(t_philosophers *philo)
{
	
	pthread_mutex_lock(&philo->l->fork);
	pthread_mutex_lock(&philo->fork);
		printf("Hilo %i\n", philo->num);
	sleep(1);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->l->fork);
}

void	*start_philo(void *arg)
{
	while(1)
	{
		printf("--------\n");
		eat_philo((t_philosophers *)arg);
		sleep(1);
	}
	return(arg);	
}

void	create_philosophers(t_philosophers *lst_philos, int n_philo)
{
	int i, j;
	t_philosophers *tmp_ph;


	j = n_philo -1 ;
	tmp_ph = lst_philos;
	i = 0;

	while(i < n_philo)
	{
		lst_philos->hilo = (pthread_t *)malloc(sizeof(pthread_t));
		pthread_mutex_init(&lst_philos->fork, NULL);
		pthread_create(lst_philos->hilo, NULL, start_philo, (void *)lst_philos);
		lst_philos = lst_philos->r;
		i++;
	}

	while(j >= 0)
	{
		pthread_join(*tmp_ph->hilo, NULL);
		tmp_ph = tmp_ph->r;
		j--;
	}
	
}


t_philosophers *new_philo(int  num)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)malloc(sizeof(t_philosophers));
	if(!philo)
		return (NULL);
	philo->r = philo;
	philo->l = philo;
	philo->num = num;
	return(philo);
}

t_philosophers *last_philo(t_philosophers *last_philo)
{
	return(last_philo->l);
}

void	add_philos(t_philosophers **lst_philos, t_philosophers *new_elem)
{
	t_philosophers *tmp;

	tmp = last_philo(*lst_philos);

	
	(*lst_philos)->l = new_elem;
	tmp->r = new_elem;
	new_elem->r= (*lst_philos);
	new_elem->l = tmp;
}



int main (int argc, char *argv[])
{
	t_philosophers *lst_philo;
	int n_philo;
	
	n_philo = min_atoi(argv[1]);
	int i;
	i = 2;
	
	lst_philo = new_philo(1);
	while (i <= n_philo)
	{
		add_philos(&lst_philo, new_philo(i));
		i++;
	}

	create_philosophers(lst_philo, n_philo);
	return(0);
	
}

/* 
int main(int argc, char *argv[])
{
	(void)argc;
	int n_philo;
	pthread_t *philo;

	t_philosophers *lst_philos;

	lst_philos = (t_philosophers *)malloc(sizeof(t_philosophers));


	

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
}*/