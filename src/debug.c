/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:08:04 by amonot            #+#    #+#             */
/*   Updated: 2025/11/07 01:45:08 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int geg_to_int(void *big)
{
	int	little;
	
	rv_memcpy(&little, big, 4); // ca fait rien
	return (little);
}

void print_process(t_process *process)
{
	int	i;

	i = 0;
	while (process)
	{
		printf("process\tn: %d\tpc:%ld\tr1->[%02X][%02X][%02X][%02X]->%d\tr2->[%02X][%02X][%02X][%02X]->%d\tr3->[%02X][%02X][%02X][%02X]->%d\tr4->[%02X][%02X][%02X][%02X]->%d\n", i, process->pc, 
			process->reg[0][0], process->reg[0][1], process->reg[0][2], process->reg[0][3], geg_to_int(process->reg[0]),
			process->reg[1][0], process->reg[1][1], process->reg[1][2], process->reg[1][3], geg_to_int(process->reg[1]),
			process->reg[2][0], process->reg[2][1], process->reg[2][2], process->reg[2][3], geg_to_int(process->reg[2]),
			process->reg[3][0], process->reg[3][1], process->reg[3][2], process->reg[3][3], geg_to_int(process->reg[3]));
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
	//printf("\033[H\033[J");
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
	printf("param %d: tab->[%02X][%02X][%02X][%02X]->%d->%d type->%d size->%d\n", n,
		param.tab[n][0], param.tab[n][1], param.tab[n][2], param.tab[n][3], 
		*(int *)&param.tab[n],param_val(param, n), (int)param.types[n], (int)param.size[n]);
}