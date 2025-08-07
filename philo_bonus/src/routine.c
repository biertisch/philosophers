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

	if (!check_death(philo))
		print_status(philo, "is thinking");
	threshold = philo->sim->time_to_die * 0.75;
	while (!check_death(philo) && get_time_ms() - philo->last_meal < threshold)
		sleep_ms(philo, 1);
}

static void	eat(t_philo *philo)
{
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	print_status(philo, "is eating");
	sleep_ms(philo, philo->sim->time_to_eat);
	while (philo->holding_forks > 0)
	{
		sem_post(philo->sim->sem_forks);
		philo->holding_forks--;
	}
}

static void	take_forks(t_philo *philo)
{
	sem_wait(philo->sim->sem_forks);
	philo->holding_forks++;
	if (!check_death(philo))
		print_status(philo, "has taken a fork");
	if (philo->sim->philo_count == 1)
	{
		while (!check_death(philo))
			sleep_ms(philo, 1);
	}
	sem_wait(philo->sim->sem_forks);
	philo->holding_forks++;
	if (!check_death(philo))
		print_status(philo, "has taken a fork");
}

static void	wait_to_be_served(t_philo *philo)
{
	if (philo->id % 2 == 0)
		sleep_ms(philo, philo->sim->time_to_eat / 2);
	else
		sleep_ms(philo, 1);
}

void	routine(t_philo *philo)
{
	wait_to_be_served(philo);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		if (philo->sim->required_meals > 0)
			check_satisfaction(philo);
		print_status(philo, "is sleeping");
		sleep_ms(philo, philo->sim->time_to_sleep);
		think_until_hungry(philo);
	}
}
