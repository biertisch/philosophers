/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:20:16 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/24 21:20:16 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*monitor_end(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	sem_wait(philo->sim->sem_over);
	clean_philo(philo);
	exit(2);
}

void	*monitor_death(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->sem_meal);
		if (get_time_ms() - philo->last_meal >= philo->sim->time_to_die)
		{
			print_status(philo, "died");
			clean_philo(philo);
			exit(1);
		}
		sem_post(philo->sem_meal);
		sleep_ms(1);
	}
	return (NULL);
}

int	create_monitor_threads(t_philo *philo)
{
	if (pthread_create(&philo->death_monitor, NULL, &monitor_death, philo) != 0)
	{
		sem_post(philo->sim->sem_over);
		return (error_exit(philo->sim, philo, ERR_8));
	}
	if (pthread_detach(philo->death_monitor) != 0)
	{
		sem_post(philo->sim->sem_over);
		return (error_exit(philo->sim, philo, ERR_9));
	}
	return (0);
}
