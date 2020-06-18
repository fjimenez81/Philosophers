/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:33:34 by fernando          #+#    #+#             */
/*   Updated: 2020/06/18 20:52:25 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

long	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_atoi(const char *str)
{
	unsigned long long int	res;
	int						signo;

	res = 0;
	signo = 0;
	while ((*str == 32) || (*str > 8 && *str < 14))
		str++;
	if (*str == '-')
		signo = 1;
	if (*str == '+' || *str == '-')
		str++;
	while ((*str != '\0') && (*str >= '0' && *str <= '9'))
	{
		if (res < 9223372036854775807)
		{
			res = (res * 10) + (*str - '0');
			str++;
		}
		else
			return ((signo - 1) * 1);
	}
	if (signo == 1)
		return (-res);
	return (res);
}

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}

void ft_putstr(char *s)
{
    int i;

    i = -1;
    while (s[++i] != '\0')
        write(1, &s[i], 1);
}

int ft_check_args(int ac, char **av)
{
    int i;
    int j;

    if ((ac != 5 && ac != 6) || ft_atoi(av[1]) == 0)
    {
        ft_putstr("\n\033[0;31mArgs are not correct!!!\n\n");
        return (0);
    }
    i = 0;
    while(++i < ac)
    {
        j = -1;
        while (av[i][++j])
            if (!ft_isdigit(av[i][j]))
            {
                ft_putstr("\n\033[0;31mArgs are not valid!!!\n\n");
                return (0);
            }
    }
    return (1);
}