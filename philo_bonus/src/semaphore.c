/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 21:04:50 by beatde-a          #+#    #+#             */
/*   Updated: 2025/08/05 21:04:50 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (i);
}

static char	*get_sem_meal_name(int philo_id)
{
	char	*name;
	int		i;

	name = malloc(sizeof(char) * 14);
	if (!name)
		return (NULL);
	ft_strlcpy(name, "/sem_meal_", 10);
	i = 13;
	name[i--] = '\0';
	while (philo_id > 0 && i > 9)
	{
		name[i--] = (philo_id % 10) + '0';
		philo_id /= 10;
	}
	while (i > 9)
		name[i--] = '0';
	return (name);
}

static int	init_semaphore(sem_t **ptr, char *name, int value, int *counter)
{
	sem_unlink(name);
	*ptr = sem_open(name, O_CREAT | O_EXCL, 0666, value);
	if (*ptr == SEM_FAILED)
		return (0);
	(*counter)++;
	return (1);
}

int	init_philo_semaphore(t_philo *philo)
{
	char	*name;

	name = get_sem_meal_name(philo->id);
	if (!name)
		return (error_exit(philo->sim, philo, ERR_6));
	if (!init_semaphore(&philo->sem_meal, name, 1, &philo->sem_initialized))
	{
		free(name);
		return (error_exit(philo->sim, philo, ERR_7));
	}
	free(name);
	return (1);
}

int	init_sim_semaphores(t_sim *sim)
{
	if (!init_semaphore(&sim->sem_forks, "/sem_forks", sim->philo_count,
			&sim->sem_initialized))
		return (0);
	if (!init_semaphore(&sim->sem_print, "/sem_print", 1,
			&sim->sem_initialized))
		return (0);
	if (!init_semaphore(&sim->sem_over, "/sem_over", 0, &sim->sem_initialized))
		return (0);
	return (1);
}
