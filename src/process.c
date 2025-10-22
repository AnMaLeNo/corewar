/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:45:07 by amonot            #+#    #+#             */
/*   Updated: 2025/10/22 17:25:52 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_process *new_process(int num, unsigned long int pc) // bzero sur reg ???
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
			process->reg[i][j++] = 0; // bzero ?
		i++;
	}
	rv_memcpy(&process->reg[0], &num, 4);
	process->pc = pc;
	process->carry = 0;
	process->next = NULL;
	return (process);
}

void inset_process(t_process *process, t_process *new) // insert "new" after "process"
{
	new->next = process->next;
	process->next = new;
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void free_process(t_process *process) // ne marche pas !
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
