/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:11:46 by amonot            #+#    #+#             */
/*   Updated: 2025/05/05 20:22:55 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include <string.h>

int live(unsigned char mem[MEM_SIZE], size_t *pc)
{
	unsigned int param;

	param = 0;
	rv_memcpy(&param, &mem[*pc + 1 % MEM_SIZE], 4);
	*pc += 5;
	return (param);
}

/* int get_param(unsigned char mem[MEM_SIZE], size_t *pc, t_op op, int n)
{
	unsigned char acb;

	*pc++;
	if (op.has_pcode)
	{
		acb = mem[*pc % MEM_SIZE];
		*pc++;
	}

}

void ld(unsigned char mem[MEM_SIZE], size_t *pc, t_op *op)
{
	
}
 */
t_op *get_instruction(int opcode, int cycle)
{
	int	i;

	i = 0;
	while (op_tab[i].name)
	{
		if (op_tab[i].opcode == opcode)
		{
			if (op_tab[i].nb_cycles <= cycle)
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

	op = get_instruction(mem[*pc % MEM_SIZE], *cycle);
	if (op == NULL)
		return (-1);
	if (ft_strcmp(op->name, "") == 0)
		r = -2;
	else if (ft_strcmp(op->name, "live") == 0)
		r = live(mem, pc);
	else
	{
		printf("instruction: %s pas fait\n", op->name);
		r = -1;
	}
	*cycle = 0;
	return (r);
}

void exec_process(t_champion champion, t_process *process, unsigned char mem[MEM_SIZE])
{
	size_t	llive[MAX_PLAYERS];
	size_t	cycle;
	int		exec;

	(void)champion;

	for (int i = 0; i < MAX_PLAYERS; i++)
	{
//		unsigned int param;

//		ft_memcpy(&param, &process->reg[0], 4);
//		printf("champion.ids: %d\n", champion.ids[i]);
//		printf("process.reg[0]: %d\n", param);
//		process = process->next;
	}

	cycle = 0;
	ft_bzero(llive, sizeof(unsigned int) * MAX_PLAYERS);
	while (true)
	{
		cycle++;
		process->cycle++;
		exec = exec_instruction(mem, &process->pc, &process->cycle);
		printf("exec_instruction: %d\n", exec);

		process = process->next;
		if (cycle == 15)
			break ;
	}
}
