/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_instruction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:50:30 by amonot            #+#    #+#             */
/*   Updated: 2025/05/07 15:55:50 by amonot           ###   ########.fr       */
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

int exec_instruction(unsigned char mem[MEM_SIZE], size_t *pc, int *cycle)
{
	t_op	*op;
	int		r;

	r = -1;
	op = get_instruction(mem[*pc % MEM_SIZE], *cycle);
	if (op == NULL)
		return (-1);
	if (ft_strcmp(op->name, "") == 0)
		r = -2;
	else if (ft_strcmp(op->name, "live") == 0)
		r = live(mem, pc);
	else
		printf("instruction: %s pas fait\n", op->name);
	*cycle = 0;
	return (r);
}
