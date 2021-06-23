/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:59:19 by krios-fu          #+#    #+#             */
/*   Updated: 2021/06/23 22:39:38 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>


typedef	struct s_philosophers
{
	pthread_t 				*hilo;
	struct s_philosophers	*r;
	struct s_philosophers	*l;
	pthread_mutex_t			fork;
	int						num;
}			t_philosophers;

/* 
** functions utils
*/
int	ft_isdigit(int c);
int	min_atoi(char *str);

#endif