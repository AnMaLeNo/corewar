/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:08:04 by amonot            #+#    #+#             */
/*   Updated: 2025/05/09 17:22:00 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void print_process(t_process *process)
{
	t_process	*p;
	int			i;

	i = 0;
	p = process;
	while (p)
	{
		printf("process\tn: %d\tpc:%ld\tr1: %d\tr2: %d\tr3: %d\tr4: %d\n", i, process->pc, *((int *)&process->reg[0]), *((int *)&process->reg[1]), *((int *)&process->reg[2]), *((int *)&process->reg[3]));
		p = p->next;
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