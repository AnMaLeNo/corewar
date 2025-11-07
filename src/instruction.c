/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:52:18 by amonot            #+#    #+#             */
/*   Updated: 2025/11/07 02:29:19 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int live(unsigned char mem[MEM_SIZE], size_t *pc)
{
	int	param;

	param = 0;
	rv_memcpy(&param, &mem[(*pc + 1) % MEM_SIZE], 4);
	*pc += 5;
	return (param);
}

bool is_valid_acb(unsigned char mem[MEM_SIZE], size_t pc, t_op op)
{
	unsigned char	acb;
	int 			type;
	int 			n;

	n = 0;
	acb = 0; // a sup !?
	mem_cpy(mem, pc + 1, &acb, 1);
	if (op.has_pcode)
	{
		while (n < 4)
		{
			type = (acb & 0b11000000 >> 2 * n) >> (6 - n * 2);
			if (n >= op.nb_params)
			{
				if (type != 0)
				{
					printf("ACB non valide (1)\n");
					return (false);
				}
			}
			//else if ((op.param_types[n] & type ) == 0) // faux
			else if ((op.param_types[n] & (-5 * type * type + 21 * type - 14) / 2) == 0) // magique
			{
				printf("ACB non valide (2), n: %d, op.param_types[n]: %d, type: %d\n", n, op.param_types[n], type);
				return (false);
			}
			n++;
		}
	}
	return (true);
}

void ld(unsigned char mem[MEM_SIZE], t_process *process, t_op op) // verifier si le registere ezsiste et fair une fonction pour manipuler les registre
{
	t_params	params;
	int		params_size;
	
	ft_bzero(&params, sizeof(t_params)); // ???
	params_size = get_param(mem, process->pc, op, &params);

	if (is_valid_acb(mem, process->pc, op) && is_valid_reg(params, op))
	{
		if (params.types[0] == DIR_CODE)
			//ft_memcpy(&process->reg[params.tab[1] - 1], &(params.tab[0]), 4); // le param est en big andien la ???!
			reg_set(process->reg, param_val(params, 1), params.tab[0]); // pas de param_val(params, 0) car on copie juste de big ver big
		else
			//mem_cpy(mem, process->pc + (short int)params.tab[0], process->reg[params.tab[1] - 1], 4); // (short int)params.tab[0] ??
			mem_cpy(mem, process->pc + param_val(params, 0),  reg_access(process->reg, param_val(params, 1)), 4);
		if (*(int *)endian_convert(reg_access(process->reg, param_val(params, 1)), sizeof(int)) == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
	process->pc += params_size + 1;
}

void st(unsigned char mem[MEM_SIZE], t_process *process, t_op op)
{
	t_params	params;
	int			params_size;
	
	ft_bzero(&params, sizeof(t_params)); // ???
	params_size = get_param(mem, process->pc, op, &params);
	if (is_valid_acb(mem, process->pc, op) && is_valid_reg(params, op))
	{
		if (params.types[1] == REG_CODE)
			//ft_memcpy(&process->reg[params.tab[1]) - 1], &process->reg[params.tab[0] - 1], 4);
			reg_set(process->reg, param_val(params, 1), reg_access(process->reg, param_val(params, 0)));
		else
			mem_set(mem, process->pc + param_val(params, 1), reg_access(process->reg, param_val(params, 0)), REG_SIZE);
	}
	process->pc += params_size + 1;
}

void add(unsigned char mem[MEM_SIZE], t_process *process, t_op op)
{
	t_params	params;
	int		params_size;
	int		result;

	ft_bzero(&params, sizeof(t_params)); // ???
	params_size = get_param(mem, process->pc, op, &params);

	// verifier si les registre exsiste
	//*(int *)&process->reg[params.tab[2] - 1] = *(int *)&process->reg[params.tab[0] - 1] + *(int *)&process->reg[params.tab[1] - 1];
	if (is_valid_acb(mem, process->pc, op) && is_valid_reg(params, op))
	{
		if (reg_access(process->reg, param_val(params, 0)) == NULL || reg_access(process->reg, param_val(params, 1)) == NULL)
			return ;
		result = *(int *)endian_convert(reg_access(process->reg, param_val(params, 0)), REG_SIZE) + *(int *)endian_convert(reg_access(process->reg, param_val(params, 1)), REG_SIZE);
		reg_set(process->reg, param_val(params, 2), endian_convert(&result, 4)); // pas sur que ca marche car pas de convertion de little verre big durant l'adition
		if (result == 0)
		process->carry = 1;
		else
			process->carry = 0;
	}
	process->pc += params_size + 1;
}

void sub(unsigned char mem[MEM_SIZE], t_process *process, t_op op)
{
	t_params	params;
	int		params_size;
	int		result;

	ft_bzero(&params, sizeof(t_params)); // ???
	params_size = get_param(mem, process->pc, op, &params);

	// verifier si les registre exsiste
	//*(int *)&process->reg[params.tab[2] - 1] = *(int *)&process->reg[params.tab[0] - 1] + *(int *)&process->reg[params.tab[1] - 1];
	if (is_valid_acb(mem, process->pc, op) && is_valid_reg(params, op))
	{		
		if (reg_access(process->reg, param_val(params, 0)) == NULL || reg_access(process->reg, param_val(params, 1)) == NULL)
			return ;
		result = *(int *)endian_convert(reg_access(process->reg, param_val(params, 0)), REG_SIZE) - *(int *)endian_convert(reg_access(process->reg, param_val(params, 1)), REG_SIZE);
		reg_set(process->reg, param_val(params, 2), endian_convert(&result, 4)); // pas sur que ca marche car pas de convertion de little verre big durant l'adition
		if (result == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
	process->pc += params_size + 1;
}

void and(unsigned char mem[MEM_SIZE], t_process *process, t_op op)
{
	t_params params;
	int params_size;
	int result;

	ft_bzero(&params, sizeof(t_params)); // ???
	params_size = get_param(mem, process->pc, op, &params);

	if (is_valid_acb(mem, process->pc, op) && is_valid_reg(params, op))
	{
		result = param_sub_val(mem, process->reg, params, 0) & param_sub_val(mem, process->reg, params, 1);
		rv_memcpy(reg_access(process->reg, param_val(params, 2)), &result, 4);
		if (result == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
	process->pc += params_size + 1;
}

void or(unsigned char mem[MEM_SIZE], t_process *process, t_op op)
{
	t_params params;
	int params_size;
	int result;

	ft_bzero(&params, sizeof(t_params)); // ???
	params_size = get_param(mem, process->pc, op, &params);

	if (is_valid_acb(mem, process->pc, op) && is_valid_reg(params, op))
	{
		result = param_sub_val(mem, process->reg, params, 0) | param_sub_val(mem, process->reg, params, 1);
		rv_memcpy(reg_access(process->reg, param_val(params, 2)), &result, 4);
		if (result == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
	process->pc += params_size + 1;
}

void xor(unsigned char mem[MEM_SIZE], t_process *process, t_op op)
{
	t_params params;
	int params_size;
	int result;

	ft_bzero(&params, sizeof(t_params)); // ???
	params_size = get_param(mem, process->pc, op, &params);

	if (is_valid_acb(mem, process->pc, op) && is_valid_reg(params, op))
	{
		result = param_sub_val(mem, process->reg, params, 0) ^ param_sub_val(mem, process->reg, params, 1);
		rv_memcpy(reg_access(process->reg, param_val(params, 2)), &result, 4);
		if (result == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
	process->pc += params_size + 1;
}

void zjmp(unsigned char mem[MEM_SIZE], t_process *process, t_op op)
{
	t_params	params;
	int		params_size;

	ft_bzero(&params, sizeof(t_params)); // ???
	params_size = get_param(mem, process->pc, op, &params);

	if (is_valid_acb(mem, process->pc, op) && is_valid_reg(params, op))
	{
		if (process->carry == 1)
		{
			process->pc += param_val(params, 0);
			return ;
		}
	}
	process->pc += params_size + 1;
	//process->pc = process->pc % MEM_SIZE; faut fair quel que chose de comme ca a la fait de chaque instruction executer
}

void ldi(unsigned char mem[MEM_SIZE], t_process *process, t_op op)
{
	t_params		params;
	int				params_size;
	int				adresse;

	ft_bzero(&params, sizeof(t_params)); // ???
	params_size = get_param(mem, process->pc, op, &params);

	//printf("ldi: pc: %ld", process->pc);
	
	print_params(params, 0);
	print_params(params, 1);
	print_params(params, 2);
	if (is_valid_acb(mem, process->pc, op) && is_valid_reg(params, op))
	{
		adresse = param_sub_val(mem, process->reg, params, 0) + param_sub_val(mem, process->reg, params, 1);
		mem_cpy(mem, adresse + process->pc, reg_access(process->reg, param_val(params, 2)), 4);
	}
	process->pc += params_size + 1;
}

/* void ldi(unsigned char mem[MEM_SIZE], size_t *pc, t_op op)
{
	int				params[MAX_PARAMS];
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
} */
