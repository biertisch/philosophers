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

void	cleanup(t_sim *sim)
{
	int	i;

	if (!sim)
		return ;
	i = 0;
	while (i < sim->threads_created)
		pthread_join(sim->philos[i++].thread, NULL);
	i = 0;
	while (i < sim->meal_mutexes_init)
		pthread_mutex_destroy(&sim->philos[i++].meal_lock);
	i = 0;
	while (i < sim->fork_mutexes_init)
		pthread_mutex_destroy(&sim->forks[i++]);
	if (sim->sim_mutex_init)
		pthread_mutex_destroy(&sim->sim_lock);
	if (sim->print_mutex_init)
		pthread_mutex_destroy(&sim->print_lock);
	free(sim->philos);
	free(sim->forks);
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
	return (0);
}
