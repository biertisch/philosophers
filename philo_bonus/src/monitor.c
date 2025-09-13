/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:11:31 by beatde-a          #+#    #+#             */
/*   Updated: 2025/08/12 12:11:31 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_satisfaction(t_philo *philo)
{
	if (philo->meals_eaten >= philo->sim->required_meals)
	{
		child_cleanup(philo);
		exit(0);
	}
	return (0);
}

int	check_death(t_philo *philo)
{
	if (get_time_ms() - philo->last_meal >= philo->sim->time_to_die)
	{
		print_status(philo, "died");
		while (philo->holding_forks > 0)
		{
			sem_post(philo->sim->sem_forks);
			philo->holding_forks--;
		}
		child_cleanup(philo);
		exit(1);
	}
	return (0);
}

void	wait_for_children(t_sim *sim)
{
	int	status;
	int	satisfied;
	int	i;

	satisfied = 0;
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1)
			{
				i = 0;
				while (i < sim->philo_count)
					kill(sim->philo_pid[i++], SIGKILL);
				while (waitpid(-1, NULL, 0) > 0)
					;
				return ;
			}
			if (WEXITSTATUS(status) == 0)
				satisfied++;
		}
	}
	if (satisfied == sim->philo_count)
		printf("%ld All philosophers are satisfied\n",
			get_time_ms() - sim->start_time);
}
