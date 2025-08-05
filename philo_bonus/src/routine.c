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
	while (get_time_ms() - philo->last_meal < threshold)
		sleep_ms(1);
}

static void	eat(t_philo *philo)
{
	sem_wait(philo->sem_meal);
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	sem_post(philo->sem_meal);
	print_status(philo, "is eating");
	sleep_ms(philo->sim->time_to_eat);
	sem_post(philo->sim->sem_forks);
	sem_post(philo->sim->sem_forks);
}

static int	take_forks(t_philo *philo)
{
	sem_wait(philo->sim->sem_forks);
	print_status(philo, "has taken a fork");
	if (philo->sim->philo_count == 1)
	{
		sleep_ms(philo->sim->time_to_die + 10);
		return (0);
	}
	sem_wait(philo->sim->sem_forks);
	print_status(philo, "has taken a fork");
	return (1);
}

static void	wait_to_be_served(t_philo *philo)
{
	if (philo->id % 2 == 0)
		sleep_ms(philo->sim->time_to_eat / 2);
	else
		sleep_ms(1);
}

void	routine(t_philo *philo)
{
	create_monitor_threads(philo);
	wait_to_be_served(philo);
	while (1)
	{
		if (!take_forks(philo))
			break ;
		eat(philo);
		if (philo->sim->required_meals > 0
			&& philo->meals_eaten >= philo->sim->required_meals)
		{
			clean_philo(philo);
			exit(0);
		}
		print_status(philo, "is sleeping");
		sleep_ms(philo->sim->time_to_sleep);
		think_until_hungry(philo);
	}
}
