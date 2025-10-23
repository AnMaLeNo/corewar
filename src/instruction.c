/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:52:18 by amonot            #+#    #+#             */
/*   Updated: 2025/10/23 17:59:03 by amonot           ###   ########.fr       */
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

void st(unsigned char mem[MEM_SIZE], t_process *process, t_op op)
{
	t_params	params;
	int			params_size;

	ft_bzero(&params, sizeof(t_params)); // ???
	params_size = get_param(mem, process->pc + 1, op, &params);
	if (params.types[1] == REG_CODE)
		ft_memcpy(&process->reg[params.tab[1] - 1], &process->reg[params.tab[0] - 1], 4);
	else
		ft_memcpy(&mem[(process->pc + params.tab[1]) % MEM_SIZE], & process->reg[params.tab[0] - 1], 4);
	process->pc += params_size + 1;
}

void zjmp(unsigned char mem[MEM_SIZE], t_process *process, t_op op)
{
	t_params	params;
	int			params_size;

	ft_bzero(&params, sizeof(t_params)); // ???
	params_size = get_param(mem, process->pc + 1, op, &params);

	if (process->carry == 1) // ici ou avant  ???
		process->pc += (char)params.tab[0];
	else
		process->pc += params_size + 1;
	process->pc = process->pc % MEM_SIZE;
}

int to_intl(void *big)
{
	int	little;

	rv_memcpy(&little, big, 4);
	return (little);
}

char to_charl(void *big)
{
	char	little;

	rv_memcpy(&little, big, 1); // ca fait rien
	return (little);
}

void ld(unsigned char mem[MEM_SIZE], t_process *process, t_op op)
{
	t_params	params;
	int			params_size;

	ft_bzero(&params, sizeof(t_params)); // ???
	params_size = get_param(mem, process->pc + 1, op, &params);

	if (params.types[0] == DIR_CODE)
		ft_memcpy(&process->reg[params.tab[1] - 1], &(params.tab[0]), 4);
	else
		ft_memcpy(&process->reg[params.tab[1] - 1], &mem[(process->pc + params.tab[0]) % MEM_SIZE], 4);
	if (to_intl(&process->reg[params.tab[1] - 1]) == 0) // a verifier
		process->carry = 1;
	else
		process->carry = 0;
	process->pc += params_size + 1;
}

void add(unsigned char mem[MEM_SIZE], t_process *process, t_op op)
{
	t_params	params;
	int			params_size;

	ft_bzero(&params, sizeof(t_params)); // ???
	params_size = get_param(mem, process->pc + 1, op, &params);

	*(int *)&process->reg[params.tab[2] - 1] = *(int *)&process->reg[params.tab[0] - 1] + *(int *)&process->reg[params.tab[1] - 1];
	if (to_charl(&process->reg[params.tab[2] - 1]) == 0)
		process->carry = 1;
	else
		process->carry = 0;
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
