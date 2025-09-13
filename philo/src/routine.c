/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:20:20 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/24 21:20:20 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	think_until_hungry(t_philo *philo)
{
	long	threshold;

	print_status(philo, "is thinking");
	threshold = philo->sim->time_to_die * 0.75;
	while (!stop_simulation(philo->sim)
		&& (get_time_ms() - philo->last_meal < threshold))
		sleep_ms(philo->sim, 1);
}

static int	eat(t_philo *philo)
{
	int	satisfied;

	satisfied = 0;
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	print_status(philo, "is eating");
	sleep_ms(philo->sim, philo->sim->time_to_eat);
	pthread_mutex_lock(&philo->meal_lock);
	philo->meals_eaten++;
	if (philo->sim->required_meals != -1
		&& philo->meals_eaten >= philo->sim->required_meals)
		satisfied = 1;
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	return (satisfied);
}

static int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	print_status(philo, "has taken a fork");
	if (philo->first_fork == philo->second_fork)
	{
		pthread_mutex_unlock(philo->first_fork);
		sleep_ms(philo->sim, philo->sim->time_to_die + 1);
		return (0);
	}
	pthread_mutex_lock(philo->second_fork);
	print_status(philo, "has taken a fork");
	return (1);
}

static void	wait_to_be_served(t_philo *philo)
{
	if (philo->id % 2 == 0)
		sleep_ms(philo->sim, philo->sim->time_to_eat / 2);
	else
		sleep_ms(philo->sim, 1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_to_be_served(philo);
	while (!stop_simulation(philo->sim))
	{
		if (!take_forks(philo))
			break ;
		if (eat(philo))
			break ;
		print_status(philo, "is sleeping");
		sleep_ms(philo->sim, philo->sim->time_to_sleep);
		think_until_hungry(philo);
	}
	return (NULL);
}
