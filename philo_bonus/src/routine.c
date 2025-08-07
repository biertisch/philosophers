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

static int	check_death(t_philo *philo)
{
	if (get_time_ms() - philo->last_meal >= philo->sim->time_to_die)
	{	
		print_status(philo, "died");
		philo->dead = 1;
		while (philo->holding_fork--)
			sem_post(philo->sim->sem_forks);
		return (1);
	}
	return (0);
}

static void	think_until_hungry(t_philo *philo)
{
	long	threshold;

	if (!philo->dead)
		print_status(philo, "is thinking");
	threshold = philo->sim->time_to_die * 0.75;
	while (get_time_ms() - philo->last_meal < threshold)
		sleep_ms(1);
}

static void	eat(t_philo *philo)
{
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	print_status(philo, "is eating");
	sleep_ms(philo->sim->time_to_eat);
	while (philo->holding_fork--)
		sem_post(philo->sim->sem_forks);
}

static void	take_forks(t_philo *philo)
{
	sem_wait(philo->sim->sem_forks);
	print_status(philo, "has taken a fork");
	if (philo->sim->philo_count == 1)
	{
		while (!check_death(philo))
			sleep_ms(1);
	}
	sem_wait(philo->sim->sem_forks);
	print_status(philo, "has taken a fork");
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
	wait_to_be_served(philo);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		if (philo->sim->required_meals > 0
			&& philo->meals_eaten >= philo->sim->required_meals)
		{
			child_cleanup(philo);
			exit(0);
			// set_status(philo, STATUS_SATISFIED);
			// break ;
		}
		print_status(philo, "is sleeping");
		sleep_ms(philo->sim->time_to_sleep);
		think_until_hungry(philo);
	}
}
