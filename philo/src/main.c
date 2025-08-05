/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:24:59 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/24 16:24:59 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_sim	sim;

	memset(&sim, 0, sizeof(t_sim));
	if (!validate_input(&sim, argc, argv))
		return (EXIT_FAILURE);
	if (!init_config(&sim, argc, argv))
		return (EXIT_FAILURE);
	if (!init_forks(&sim))
		return (EXIT_FAILURE);
	if (!init_philos(&sim))
		return (EXIT_FAILURE);
	pthread_mutex_lock(&sim.sim_lock);
	sim.sim_over = 0;
	pthread_mutex_unlock(&sim.sim_lock);
	while (!stop_sim(&sim))
	{
		monitor(&sim);
		usleep(500);
	}
	cleanup(&sim);
	printf("End of simulation\n");
	return (EXIT_SUCCESS);
}
