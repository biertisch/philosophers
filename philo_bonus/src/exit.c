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
				break ;
			}
			if (WEXITSTATUS(status) == 0)
				satisfied++;
		}
	}
	if (satisfied == sim->philo_count)
		printf("%ld All philosophers are satisfied\n",
			get_time_ms() - sim->start_time);
}

void	child_cleanup(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->sim->philo_count)
	{
		sem_close(philo->sim->sem_meal[i]);
		sem_close(philo->sim->sem_status[i++]);
	}
	sem_close(philo->sim->sem_print);
	sem_close(philo->sim->sem_forks);
}

void	cleanup(t_sim *sim)
{
	int	i;

	if (!sim)
		return ;
	i = 0; 
	while (i < sim->philo_count)
	{
		if (sim->sem_meal && sim->sem_meal[i])
			sem_close(sim->sem_meal[i]);
		if (sim->sem_status && sim->sem_status[i])
			sem_close(sim->sem_status[i]);
		i++;
    }
	if (sim->sem_print)
		sem_close(sim->sem_print);
	if (sim->sem_forks)
		sem_close(sim->sem_forks);
	free(sim->philo_pid);
	free(sim->philos);
	free(sim->sem_meal);
	free(sim->sem_status);
	memset(sim, 0, sizeof(t_sim));
}

int	error_exit(t_sim *sim, char *error_msg)
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
	cleanup(sim);
	exit(1);
}
