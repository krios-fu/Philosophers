/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:15:58 by krios-fu          #+#    #+#             */
/*   Updated: 2021/06/30 00:13:23 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	start_process(t_philosophers *lst_philos)
{
	start_philos(lst_philos, lst_philos->size_lst);
	join_threads(lst_philos, lst_philos->size_lst);
	free_resources(lst_philos, lst_philos->size_lst);
}

int	create_lst_philos(int argc, char *argv[], t_philosophers *lst_philos)
{
	struct timeval	start;
	int				i;
	int				n_philo;

	if ((argc == 5 || argc == 6) && check_arg(argv) && min_atoi(argv[1]) > 1)
	{
		if (argv[5] && min_atoi(argv[5]) == 0)
			return (0);
		n_philo = min_atoi(argv[1]);
		i = 2;
		gettimeofday(&start, NULL);
		lst_philos = new_philo(1, new_time(argv), start, n_philo);
		while (i <= n_philo)
		{
			add_philos(&lst_philos,
				new_philo(i, new_time(argv), start, n_philo));
			i++;
		}
		start_process(lst_philos);
	}
	else
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_philosophers	*lst_philos;

	if (create_lst_philos(argc, argv, lst_philos) == 0)
		printf("philo: Error syntax arguments\n");
	return (0);
}
