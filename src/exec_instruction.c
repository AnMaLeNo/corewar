/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_instruction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:50:30 by amonot            #+#    #+#             */
/*   Updated: 2025/10/29 18:32:28 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_op *get_instruction(int opcode, int cycle)
{
	int	i;

	i = 0;
	while (op_tab[i].name)
	{
		if (op_tab[i].opcode == opcode)
		{
			if (op_tab[i].nb_cycles <= cycle) // ??? < ou <= ???
				return (&op_tab[i]);
			else
				return (NULL);
		}
		i++;
	}
	return (&op_tab[0]);
}

int exec_instruction(unsigned char mem[MEM_SIZE], t_process *process)
{
	t_op	*op;
	int		r;

	r = -2;
	op = get_instruction(mem[process->pc % MEM_SIZE], process->cycle);
	if (op == NULL)
		return (-1);
	if (ft_strcmp(op->name, "") == 0)
		process->pc++;
	else if (ft_strcmp(op->name, "live") == 0)
		r = live(mem, &process->pc);
	else if (ft_strcmp(op->name, "ld") == 0)
		ld(mem, process, *op);
	else if (ft_strcmp(op->name, "st") == 0)
	 	st(mem, process, *op);
	// else if (ft_strcmp(op->name, "add") == 0)
	// 	add(mem, process, *op);
	// else if (ft_strcmp(op->name, "zjmp") == 0)
	// 	zjmp(mem, process, *op);
	else
	{
		printf("instruction: %s pas fait\n", op->name);
	}
	process->cycle = 0;
	return (r);
}
