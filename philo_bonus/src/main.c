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

static void	wait_for_children(t_sim *sim)
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
				while (i++ < sim->philo_count)
					sem_post(sim->sem_over);
				i = 0;
				while (i++ < sim->philo_count)
					sem_post(sim->sem_print);
			}
			if (WEXITSTATUS(status) == 0)
				satisfied++;
		}
	}
	if (satisfied == sim->philo_count)
		printf("%ld All philosophers are satisfied\n",
			get_time_ms() - sim->start_time);
}

int	main(int argc, char **argv)
{
	t_sim	sim;

	memset(&sim, 0, sizeof(t_sim));
	validate_input(&sim, argc, argv);
	init_config(&sim, argc, argv);
	create_children(&sim);
	wait_for_children(&sim);
	clean_sim(&sim);
	printf("End of simulation\n");
	return (0);
}
