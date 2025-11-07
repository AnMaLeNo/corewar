/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:11:46 by amonot            #+#    #+#             */
/*   Updated: 2025/11/07 01:41:42 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include <string.h>

int report_live(t_champion *champion, int num, size_t cycle)
{
	int i;

	i = 0;
	while (i < champion->nbr)
	{
		if (champion->ids[i] == num)
		{
			champion->live[i] = cycle;
			printf("champion: %d reported alive at cycle: %ld\t i = %d\n", champion->ids[i], champion->live[i], i);
			return (0);
		}
		i++;
	}
	printf("champion: %d does not exist\n", num);
	return (-1);
}

void exec_process(t_champion champion, t_process *process, unsigned char mem[MEM_SIZE])
{
	int		exec;
	t_vm	vm;


	vm.cycle = 0;
	vm.last_born = process;
	vm.cycle_to_die = CYCLE_TO_DIE;
	vm.last_check = 0;
	vm.nb_check = 0;
	vm.winner = -42;
	while (true)
	{
		while (process)
		{
			process->cycle++; // ici ou apret exec instruction ??
			exec = exec_instruction(mem, process);
			if (exec >= 0)
			{
				report_live(&champion, exec, vm.cycle + 1); // pour quoi vm.cycle + 1 ?
				vm.nb_live++;
			}
			process = process->next;
		}
		process = vm.last_born;
		vm.cycle++;
		
		debug(mem, vm, process);
		
		if (check(&vm, champion))
			break;
		
/* 		if (vm.cycle == 35)
			break ; */
	}
	printf("cycle: %ld\n", vm.cycle);
	if (vm.winner != -42)
		printf("the winner is : %d\n", vm.winner);
	else
	{
		printf("NO winner...\n");
	}
}
