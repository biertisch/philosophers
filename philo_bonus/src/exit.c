/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:17:08 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/24 20:17:08 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	clean_philo(t_philo *philo)
{
	if (!philo)
		return ;
	if (philo->sem_initialized)
		sem_close(philo->sem_meal);
	free(philo);
}

void	clean_sim(t_sim *sim)
{
	if (!sim)
		return ;
	while (sim->sem_initialized)
	{
		if (sim->sem_initialized == 3)
			sem_close(sim->sem_over);
		else if (sim->sem_initialized == 2)
			sem_close(sim->sem_print);
		else if (sim->sem_initialized == 1)
			sem_close(sim->sem_forks);
		sim->sem_initialized--;
	}
	free(sim->philo_pid);
	memset(sim, 0, sizeof(t_sim));
}

int	error_exit(t_sim *sim, t_philo *philo, char *error_msg)
{
	int	len;

	len = 0;
	if (error_msg)
	{
		while (error_msg[len])
			len++;
		write(2, "Error: ", 7);
		write(2, error_msg, len);
		write(2, "\n", 1);
	}
	clean_sim(sim);
	clean_philo(philo);
	exit(1);
}
