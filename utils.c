/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:58:28 by krios-fu          #+#    #+#             */
/*   Updated: 2021/06/22 02:09:42 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	min_atoi(char *str)
{
	long	nb;
	int		i;

	nb = 0;
	i = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		nb += str[i] - '0';
		if (str[i + 1] != '\0')
			nb *= 10;
		else
			return (nb);
		i++;
	}
	return (-1);
}
