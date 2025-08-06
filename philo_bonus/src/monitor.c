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

void	set_status(t_philo *philo, int type)
{
	sem_wait(philo->sem_status);
	if (type == STATUS_DEAD)
		philo->dead = 1;
	else
		philo->satisfied = 1;
	sem_post(philo->sem_status);
}

int	get_status(t_philo *philo, int type)
{
	int	status;
	
	sem_wait(philo->sem_status);
	if (type == STATUS_DEAD)
		status = philo->dead;
	else
		status = philo->satisfied;
	sem_post(philo->sem_status);
	return (status);
}

static void	*monitor_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->sem_meal);
		if (get_time_ms() - philo->last_meal >= philo->sim->time_to_die)
		{	
			sem_post(philo->sem_meal);
			print_status(philo, "died");
			set_status(philo, STATUS_DEAD);
			break ;
		}
		sem_post(philo->sem_meal);
		if (get_status(philo, STATUS_SATISFIED))
			break ;
		usleep(1000);
	}
	return (NULL);
}

int	create_monitor_thread(t_philo *philo)
{
	if (pthread_create(&philo->monitor, NULL, &monitor_death, philo) != 0)
		return (error_exit(philo->sim, ERR_6));
	return (0);
}
