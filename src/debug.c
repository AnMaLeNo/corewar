/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:08:04 by amonot            #+#    #+#             */
/*   Updated: 2025/10/27 17:33:22 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void print_process(t_process *process)
{
	int	i;

	i = 0;
	while (process)
	{
		printf("process\tn: %d\tpc:%ld\tr1->[%02X][%02X][%02X][%02X]->%d\tr2->[%02X][%02X][%02X][%02X]->%d\tr3->[%02X][%02X][%02X][%02X]->%d\tr4->[%02X][%02X][%02X][%02X]->%d\n", i, process->pc, 
			process->reg[0][0], process->reg[0][1], process->reg[0][2], process->reg[0][3], *((int *)&process->reg[0]),
			process->reg[1][0], process->reg[1][1], process->reg[1][2], process->reg[1][3], *((int *)&process->reg[1]),
			process->reg[2][0], process->reg[2][1], process->reg[2][2], process->reg[2][3], *((int *)&process->reg[2]),
			process->reg[3][0], process->reg[3][1], process->reg[3][2], process->reg[3][3], *((int *)&process->reg[3]));
		process = process->next;
		i++;
	}
}

t_op *operation(int opcode)
{
	int	i;

	i = 0;
	while (op_tab[i].name)
	{
		if (op_tab[i].opcode == opcode)
		{
			return (&op_tab[i]);
		}
		i++;
	}
	return (&op_tab[0]);
}

void live_mem(unsigned char mem[MEM_SIZE], int l, int h, size_t pc)
{
	unsigned long int i;

	i = 0;
	printf("\033[H\033[J");
	while (i < MEM_SIZE)
	{
		if (i == pc % MEM_SIZE)
			printf("\033[31m%02X \033[0m", mem[i]);
		else
			printf("%02X ", mem[i]);
		i++;
		if (i % (l * h) == 0)
			break;
		if (i % l == 0)
			printf("\n");
	}
	printf("\n");
}

void debug(unsigned char mem[MEM_SIZE], t_vm vm, t_process *process)
{
	t_op *op = operation(mem[process->pc % MEM_SIZE]);
	live_mem(mem, 16, 4, process->pc);
	printf("cycle: %ld\tcycle_to_die: %d\tnb_live: %d\n", vm.cycle, vm.cycle_to_die, vm.nb_live);
	print_process(process);
	printf("\033[32m%s\tnb_cycles: %d\033[0m\n", op->name, op->nb_cycles);
	if (getchar() < 0)
		usleep(500);
}

void print_params(t_params param, int n)
{
	printf("param %d: tab->[%02X][%02X][%02X][%02X]->%d type->%d size->%d\n", n,
		((unsigned char *)&param.tab[n])[0], ((unsigned char *)&param.tab[n])[1], ((unsigned char *)&param.tab[n])[2], ((unsigned char *)&param.tab[n])[3], 
		param.tab[n], param.types[n], param.size[n]);
}