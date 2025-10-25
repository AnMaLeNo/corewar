/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:36:27 by amonot            #+#    #+#             */
/*   Updated: 2025/10/25 20:06:00 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int read_int(char *mem) // ??
{
	unsigned int n;
	int i;

	i = 0;
	n = 0;
	while (i < 4)
	{
		n = n << 8;
		n += mem[i];
		i++;
	}
	return (n);
}

int ft_strcmp(const char *first, const char *second)
{
	size_t	i;

	i  = 0;
	while (first[i] == second[i] && first[i] && second[i])
		i++;
	return (first[i] - second[i]);
}

void * rv_memcpy(void *destination, const void *source, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = size - 1;
	while (i < size)
	{
		((char *)destination)[i] = ((const char *)source)[j];
		i++;
		j--;
	}
	return (destination);
}

void * ft_memcpy(void *destination, const void *source, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		((char *)destination)[i] = ((const char *)source)[i];
		i++;
	}
	return (destination);
}

unsigned char *mem_acces(unsigned char mem[MEM_SIZE], ssize_t t)
{
	if (t < 0) {
		//printf("t: %ld, res: %ld\n", t, MEM_SIZE - 1 + t % -MEM_SIZE);
		return (&mem[MEM_SIZE + t % -MEM_SIZE]);
	}
	else {
		//printf("t: %ld, res: %ld\n", t, t % MEM_SIZE);
		return (&mem[t % MEM_SIZE]);
	}
}


unsigned char *mem_get(unsigned char mem[MEM_SIZE], ssize_t t, int size) // attention a la taille de size (16 max)
{
	static unsigned char buffer[16];
	for (int i = 0; i < size; i++)
			buffer[i] = *mem_acces(mem, t + i);
	return (buffer);
}