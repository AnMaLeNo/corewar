/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:11:46 by amonot            #+#    #+#             */
/*   Updated: 2025/05/06 20:26:16 by amonot           ###   ########.fr       */
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

int param_size(t_op op, unsigned char acb, int n)
{
	int 			param;

	if (op.has_pcode)
	{
		param = (acb & 0b11000000 >> 2 * n) >> (6 - n * 2);
		if (param == REG_CODE)
			return (PARAM_REGISTER);
		else if (param == DIR_CODE)
			return (PARAM_DIRECT / (1 + op.has_idx));
		else if (param == IND_CODE)
			return (PARAM_INDIRECT);
		return (PARAM_UNKNOWN);
	}
	else
	{
		if (op.param_types[n] == PARAM_DIRECT && op.has_idx)
			return (PARAM_DIRECT / 2);
		else
			return (op.param_types[n]);
	}
}

int get_param(unsigned char mem[MEM_SIZE], size_t pc, t_op op, unsigned int params[MAX_PARAMS])
{
	unsigned char	acb;
	int				size;
	int				i;

	i = 0;
	size = 0;
	acb = mem[(pc + size) % MEM_SIZE];
	if (op.has_pcode)
		size++;
	while (i < op.nb_params)
	{
		printf("param: %d, size: %d\n", i + 1, param_size(op, acb, i));
		rv_memcpy(&params[i], &mem[(pc + size) % MEM_SIZE], param_size(op, acb, i));
		size += param_size(op, acb, i);
		i++;
	}
	return (size);
}

void ld(unsigned char mem[MEM_SIZE], size_t *pc, t_op op)
{
	unsigned int	params[MAX_PARAMS];
	int				i;
	int				params_size;

	i = 0;
	*pc += 1;
	ft_bzero(&params, 4 * MAX_PARAMS);
	params_size = get_param(mem, *pc, op, params);
	while(i < op.nb_params)
	{
		printf("param: %d	value: %d\n", i + 1, params[i]);
		i++;
	}
	*pc += params_size;
	printf("params_size: %d\n", params_size);
}

void ldi(unsigned char mem[MEM_SIZE], size_t *pc, t_op op)
{
	unsigned int	params[MAX_PARAMS];
	int				i;
	int				params_size;

	i = 0;
	*pc += 1;
	ft_bzero(&params, 4 * MAX_PARAMS);
	params_size = get_param(mem, *pc, op, params);
	while(i < op.nb_params)
	{
		printf("param: %d	value: %d\n", i + 1, params[i]);
		i++;
	}
	*pc += params_size;
	printf("params_size: %d\n", params_size);
}

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

	r = -1;
	op = get_instruction(mem[*pc % MEM_SIZE], *cycle);
	if (op == NULL)
		return (-1);
	if (ft_strcmp(op->name, "") == 0)
		r = -2;
	else if (ft_strcmp(op->name, "live") == 0)
		r = live(mem, pc);
	else if (ft_strcmp(op->name, "ld") == 0)
		ld(mem, pc, *op);
	else if (ft_strcmp(op->name, "ldi") == 0)
		ldi(mem, pc, *op);
	else
		printf("instruction: %s pas fait\n", op->name);
	*cycle = 0;
	return (r);
}

int report_live(t_champion *champion, int num, size_t cycle)
{
	int i;

	i = 0;
	while (i < champion->nbr)
	{
		if (champion->ids[i] == num)
		{
			champion->live[i] = cycle;
			//printf("champion: %d reported alive at cycle: %ld\t i = %d\n", champion->ids[i], champion->live[i], i);
			return (0);
		}
		i++;
	}
	printf("champion: %d does not exist\n", num);
	return (-1);
}

int check_winner(t_vm *vm, t_champion champion)
{
	int i;
	int p;
	int num;

	i = 0;
	p = 0;
	while (i < champion.nbr)
	{
		printf("champion.ids[i]: %d\tchampion.live[i]: %ld\n", champion.ids[i], champion.live[i]);
		if (champion.ids[i] != -1 && champion.live[i] != 0)
		{
			num = champion.ids[i];
			p++;
		}
		i++;
	}
	if (p == 1)
	{
		vm->winner = num;
		return (1);
	}
	else if (p == 0)
	{
		vm->winner = -42;
		return (1);
	}
	return (0);
}

int check_live(t_vm *vm, t_champion champion)
{
	int i;

	i = 0;
	while (i < champion.nbr)
	{
		if (check_winner(vm, champion))
			return (1);
		if (vm->cycle - champion.live[i] >= vm->cycle_to_die)
		{
			if (champion.ids[i] >= 0)
			{
				printf("champion: %d die\n", champion.ids[i]);
				champion.ids[i] = -1;
			}
		}
		i++;
	}
	return (check_winner(vm, champion));
}

int check(t_vm *vm, t_champion champion)
{
	if (vm->last_check + vm->cycle_to_die == vm->cycle)
	{
		vm->last_check = vm->cycle; // ???
		if (check_live(vm, champion))
			return (1);
		vm->nb_check++;
		if (vm->nb_live >= NBR_LIVE)
		{
			vm->cycle_to_die -= CYCLE_DELTA;
			vm->nb_check = 0;	
		}
		else if (vm->nb_check == MAX_CHECKS)
		{
			vm->cycle_to_die -= CYCLE_DELTA;
			vm->nb_check = 0;
		}
	}
	return (0);
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
			process->cycle++;
			exec = exec_instruction(mem, &process->pc, &process->cycle);
			if (exec >= 0)
			{
				printf("1121 : %d\n", champion.ids[MAX_PLAYERS - 1]);

				report_live(&champion, exec, vm.cycle + 1);
			}
			else
				printf("exec: %d\n", exec);
			process = process->next;
		}
		process = vm.last_born;
		vm.cycle++;

		if (check(&vm, champion))
			break;
		printf("cycle: %ld\n", vm.cycle);

/* 		if (vm.cycle == 10)
			break ; */
	}
	if (vm.winner != -42)
		printf("the winner is : %d\n", vm.winner);
	else
	{
		printf("NO winner...\n");
	}
}
