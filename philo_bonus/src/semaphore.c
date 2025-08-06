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

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
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

static char	*get_philo_sem_name(char *base, int id)
{
	char	*name;
	int		base_len;

	base_len = 0;
	while (base[base_len])
		base_len++;
	name = malloc(sizeof(char) * (base_len + 4));
	if (!name)
		return (NULL);
	ft_strlcpy(name, base, base_len + 4);
	name[base_len] = (id / 100) % 10 + '0';
	name[base_len + 1] = (id / 10) % 10 + '0';
	name[base_len + 2] = id % 10 + '0';
	name[base_len + 3] = '\0';
	return (name);
}

static int	init_semaphore(sem_t **ptr, char *name, int value)
{
	sem_unlink(name);
	*ptr = sem_open(name, O_CREAT | O_EXCL, 0666, value);
	if (*ptr == SEM_FAILED)
		return (0);
	return (1);
}

static int	init_philo_semaphore(char *base, sem_t **array, int i)
{
	char	*name;
	int		ret;

	name = get_philo_sem_name(base, i + 1);
	if (!name)
		return (0);
	ret = init_semaphore(&array[i], name, 1);
	free(name);
	name = NULL;
	return (ret);
}

int	init_semaphores(t_sim *sim)
{
	int	i;
	
	if (!init_semaphore(&sim->sem_forks, "/sem_forks", sim->philo_count))
		return (0);
	if (!init_semaphore(&sim->sem_print, "/sem_print", 1))
		return (0);
	i = 0;
	while (i < sim->philo_count)
	{
		if (!init_philo_semaphore("/sem_meal_", sim->sem_meal, i))
			return (0);
		if (!init_philo_semaphore("/sem_status_", sim->sem_status, i))
			return (0);
		i++;
	}
	return (1);
}
