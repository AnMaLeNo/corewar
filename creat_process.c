/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:45:07 by amonot            #+#    #+#             */
/*   Updated: 2025/05/06 17:02:42 by amonot           ###   ########.fr       */
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

/* void inset_process(t_process *process, t_process *new)
{
	new->next = process->next;
	process->next = new;
} */

void free_process(t_process *process) // a test
{
	t_process	*tmp;

	while (process)
	{
		tmp = process;
		process = process->next;
		free(tmp);
	}
}

void creat_process(t_champion champion, unsigned char mem[MEM_SIZE])
{
	t_process	*process;
	t_process	*last_born;
	int			p;

	p = 1;
	process = NULL;
	last_born = new_process(champion.ids[0], 0 * (MEM_SIZE / champion.nbr));
	if (last_born == NULL)
	{
		perror("new_process");
		return ;
	}
	process = last_born;
	while (p < champion.nbr)
	{
		last_born = new_process(champion.ids[p], p * (MEM_SIZE / champion.nbr));
		if (last_born == NULL)
		{
			perror("new_process");
			break;
		}
		last_born->next = process;
		process = last_born;
		p++;
	}
	//process = last_born;
	p = 0;
	while (p < champion.nbr)
	{
		int r;

		rv_memcpy(&r, &process->reg[0], 4);
		printf("process r1: %d\n", r);
		process = process->next;
		p++;
	}
	exec_process(champion, last_born, mem);
	free_process(last_born);
}
