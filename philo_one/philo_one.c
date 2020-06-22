/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 18:14:24 by fernando          #+#    #+#             */
/*   Updated: 2020/06/22 15:23:20 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*meal_loop(void *ptr)
{
	t_args	*s;
	int		i;

	s = (t_args *)ptr;
	pthread_mutex_lock(s->meals);
	i = -1;
	while (++i < s->nb_phi)
		pthread_mutex_lock(s->meals);
	pthread_mutex_unlock(s->state);
	return (NULL);
}

void	*death_loop(void *ptr)
{
	t_args	*s;
	int		alive;
	int		hungry;

	s = (t_args *)ptr;
	alive = 1;
	hungry = 1;
	while (1)
	{
		if (ft_time() - s->last_meal > s->t_die && alive)
		{
			ft_message(s->t_start, s->who, "died");
			pthread_mutex_unlock(s->state);
			alive = 0;
		}
		else if (s->meal_cnt >= s->nb_eat && hungry)
		{
			pthread_mutex_unlock(s->meals);
			hungry = 0;
		}
	}
	return (NULL);
}

void *makeActions(void *param)
{
    t_args		*s;

	s = (t_args *)param;
	pthread_create(&s->tid, NULL, death_loop, s);
    while (1)
	{
		pthread_mutex_lock(&s->fork);
		pthread_mutex_lock(s->next);
		ft_message(s->t_start, s->who, "has taken a fork");
		ft_message(s->t_start, s->who, "has taken a fork");
		s->last_meal = ft_time();
		ft_message(s->t_start, s->who, "is eating");
		usleep(s->t_eat * 1000);
		pthread_mutex_unlock(&s->fork);
		pthread_mutex_unlock(s->next);
		ft_message(s->t_start, s->who, "is sleeping");
		usleep(s->t_sleep * 1000);
		ft_message(s->t_start, s->who, "is thinking");
		s->meal_cnt++;
		if (s->meal_cnt == s->nb_eat)
			pthread_mutex_lock(s->state);
	}
	return (NULL);
}

void philo_one(t_args *s)
{
	pthread_mutex_t	meals;
	pthread_mutex_t	state;
	int i;
	
	pthread_mutex_init(&meals, NULL);
	pthread_mutex_init(&state, NULL);
	pthread_mutex_lock(&state);
	i = -1;
	while (++i < s[0].nb_phi)
	{
		s[i].meals = &meals;
		s[i].state = &state;
		pthread_create(&s->tid, NULL, &makeActions, &s[i]);
	}
	if (s[0].nb_eat > -1)
		pthread_create(&s->tid, NULL, &meal_loop, &s[0]);
	pthread_mutex_lock(&state);
	i = -1;
    while(++i < s[0].nb_phi)
        pthread_mutex_destroy(&s[i].fork);
	pthread_mutex_destroy(&meals);
	pthread_mutex_destroy(&state);
	free(s);
}

int main(int ac, char **av)
{
    t_args *s;
    
    if (!ft_check_args(ac, av) ||
        !(s = malloc(sizeof(t_args) * ft_atoi(av[1]))))
		return (1);
    int i = -1;
    while(++i < ft_atoi(av[1]))
    {
        pthread_mutex_init(&s[i].fork, NULL);
		s[i].nb_phi = ft_atoi(av[1]);
		s[i].t_die = ft_atoi(av[2]);
		s[i].t_eat = ft_atoi(av[3]);
		s[i].t_sleep = ft_atoi(av[4]);
		s[i].nb_eat = (ac == 6) ? ft_atoi(av[5]) : -1;
        s[i].t_start = ft_time();
		s[i].last_meal = s[i].t_start;
		s[i].meal_cnt = 0;
		s[i].who = i + 1;
		s[i].next = (i != 0) ? &s[i - 1].fork : &s[s[0].nb_phi - 1].fork;
    }
	philo_one(s);
    return (0);
}