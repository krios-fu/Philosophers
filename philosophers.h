/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:59:19 by krios-fu          #+#    #+#             */
/*   Updated: 2021/06/24 20:14:48 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>




typedef struct s_time
{
	useconds_t	die;
	useconds_t	eat;
	useconds_t	sleep;
	
}				t_time;


typedef	struct s_philosophers
{
	struct s_time			*time_to;
	struct timeval			start;
	struct timeval			end;
	struct s_philosophers	*right;
	struct s_philosophers	*left;
	pthread_mutex_t			fork;
	pthread_t 				*hilo;
	int						num;
}			t_philosophers;

/* 
** functions utils
*/
int		ft_isdigit(int c);
int		min_atoi(char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);

#endif