/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:45:07 by amonot            #+#    #+#             */
/*   Updated: 2025/05/05 19:52:36 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

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
	rv_memcpy(process->reg[0], &num, 4); // ?? pas sur
	process->pc = pc;
	process->carry = 0;
	process->next = NULL;
	process->cycle = 0;
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
	process = process->next;
	tmp->next = NULL;
	while (process)
	{
		tmp = process;
		process = process->next;
		free(tmp);
	}
}

// t_header champion[MAX_PLAYERS], int nbr, int ch_num[MAX_PLAYERS]
void creat_process(t_champion champion, unsigned char mem[MEM_SIZE])
{
	t_process	*process;
	t_process	*new;
	int			p;

	(void)champion;
	process = new_process(champion.ids[0], 0 * (MEM_SIZE / champion.nbr));
	if (process == NULL)
	{
		perror("new_process");
		return ;
	}
	p = 1;
	process->next = process;
	while (p < champion.nbr)
	{
		new = new_process(champion.ids[p], p * (MEM_SIZE / champion.nbr));
		if (new == NULL)
		{
			perror("new_process");
			break;
		}
		inset_process(process, new);
		p++;
	}
	process = process->next;
	p = 0;
	while (p < champion.nbr)
	{
		printf("process r1: %d\n", *(int *)(void *)(&process->reg[0]));
		process = process->next;
		p++;
	}
	exec_process(champion, process, mem);
	free_process(process);
}
