/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 17:11:34 by fernando          #+#    #+#             */
/*   Updated: 2020/06/18 20:51:59 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int		ft_nbrlen(long n)
{
	int		size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		size++;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

void	ft_charfill(char *buffer, char *str, int *i)
{
	int	j;

	j = 0;
	while (str[j])
		buffer[(*i)++] = str[j++];
}

void	ft_numfill(char *buffer, long nbr, int *i)
{
	long	div;

	if (nbr == 0)
	{
		buffer[(*i)++] = '0';
		return ;
	}
	div = 1000000000;
	while (nbr / div == 0)
		div = div / 10;
	while (div > 0)
	{
		buffer[(*i)++] = nbr / div + '0';
		nbr = nbr % div;
		div = div / 10;
	}
}

void	ft_message(long time, int who, char *what)
{
	long	stamp;
	char	*buffer;
	int		size;
	int		i;

	stamp = ft_time() - time;
	size = ft_nbrlen(stamp) + ft_nbrlen(who) + ft_strlen(what) + 4;
	if (!(buffer = malloc(sizeof(char) * size)))
		return ;
	i = 0;
	ft_numfill(buffer, stamp, &i);
	buffer[i++] = ' ';
	ft_numfill(buffer, who, &i);
	buffer[i++] = ' ';
	ft_charfill(buffer, what, &i);
	buffer[i++] = '\n';
	write(1, buffer, size - 1);
	free(buffer);
}