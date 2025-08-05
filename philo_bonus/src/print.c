/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:46:45 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/29 17:46:45 by beatde-a         ###   ########.fr       */
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

char	*get_sem_meal_name(int philo_id)
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

void	print_status(t_philo *philo, char *msg)
{
	long		timestamp;

	sem_wait(philo->sim->sem_print);
	timestamp = get_time_ms() - philo->sim->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, msg);
	sem_post(philo->sim->sem_print);
}
