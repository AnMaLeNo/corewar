/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:45:07 by amonot            #+#    #+#             */
/*   Updated: 2025/05/04 22:59:51 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

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

t_process *new_process(int num, unsigned long int pc)
{
	t_process		*process;
	unsigned int	i;
	unsigned int	j;
	
	process = malloc(sizeof(t_process));
	if (process == NULL)
		return (NULL);
	i = 0;
	while (i < REG_NUMBER)
	{
		j = 0;
		while (j < REG_SIZE)
			process->reg[i][j++] = 0;
		i++;
	}
	ft_memcpy(process->reg[0], num, 4);
	process->pc = pc;
	process->carry = 0;
	process->next = NULL;
	return (process);
}

void inset_process(t_process *process, t_process *new)
{
	new->next = process->next;
	process->next = new;
}

void free_process(t_process *process) // a test
{
	t_process	*tmp;

	tmp = process;
	tmp->next = NULL;
	process = process->next;
	while (process && process->next)
	{
		tmp = process;
		process = process->next;
		free(tmp);
	}
}

void creat_process(t_header champion[MAX_PLAYERS], int nbr, int ch_num[MAX_PLAYERS])
{
	t_process	*process;
	t_process	*new;
	int			p;

	process = new_process(ch_num[p], 0 * (MEM_SIZE / nbr));
	if (process == NULL)
		return (-1);
	process->next = process;
	p = 1;
	while (p < nbr)
	{
		new = new_process(ch_num[p], p * (MEM_SIZE / nbr));
		if (new == NULL)

	}
}