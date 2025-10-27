/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:52:18 by amonot            #+#    #+#             */
/*   Updated: 2025/10/27 18:45:23 by amonot           ###   ########.fr       */
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

// void st(unsigned char mem[MEM_SIZE], t_process *process, t_op op)
// {
// 	t_params	params;
// 	int			params_size;

// 	ft_bzero(&params, sizeof(t_params)); // ???
// 	params_size = get_param(mem, process->pc, op, &params);
// 	if (params.types[1] == REG_CODE)
// 		ft_memcpy(&process->reg[params.tab[1] - 1], &process->reg[params.tab[0] - 1], 4);
// 	else
// 		mem_set(mem, process->pc + (short int)params.tab[1], &process->reg[params.tab[0] - 1], 4);
// 	process->pc += params_size + 1;
// }

// void zjmp(unsigned char mem[MEM_SIZE], t_process *process, t_op op)
// {
// 	t_params	params;
// 	int			params_size;

// 	ft_bzero(&params, sizeof(t_params)); // ???
// 	params_size = get_param(mem, process->pc, op, &params);

// 	if (process->carry == 1) // ici ou avant  ???
// 		process->pc += (char)params.tab[0];
// 	else
// 		process->pc += params_size + 1;
// 	process->pc = process->pc % MEM_SIZE;
// }

char to_charl(void *big)
{
	char	little;

	rv_memcpy(&little, big, 1); // ca fait rien
	return (little);
}

void ld(unsigned char mem[MEM_SIZE], t_process *process, t_op op) // verifier si le registere ezsiste et fair une fonction pour manipuler les registre
{
	t_params	params;
	int		params_size;

	ft_bzero(&params, sizeof(t_params)); // ???
	params_size = get_param(mem, process->pc, op, &params);
	print_params(params, 0); // check parame size 2 | OK
	print_params(params, 1);

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
	process->pc += params_size + 1;
}

// void add(unsigned char mem[MEM_SIZE], t_process *process, t_op op)
// {
// 	t_params	params;
// 	int			params_size;

// 	ft_bzero(&params, sizeof(t_params)); // ???
// 	params_size = get_param(mem, process->pc, op, &params);

// 	// verifier si les registre exsiste
// 	*(int *)&process->reg[params.tab[2] - 1] = *(int *)&process->reg[params.tab[0] - 1] + *(int *)&process->reg[params.tab[1] - 1];
// 	if (to_charl(&process->reg[params.tab[2] - 1]) == 0)
// 		process->carry = 1;
// 	else
// 		process->carry = 0;
// 	process->pc += params_size + 1;
// }

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
