/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:52:18 by amonot            #+#    #+#             */
/*   Updated: 2025/05/07 16:06:05 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int live(unsigned char mem[MEM_SIZE], size_t *pc)
{
	unsigned int param;

	param = 0;
	rv_memcpy(&param, &mem[*pc + 1 % MEM_SIZE], 4);
	*pc += 5;
	return (param);
}

int st(unsigned char mem[MEM_SIZE], size_t *pc, t_op op)
{
	unsigned int	params[MAX_PARAMS];
	int				params_size;

	ft_bzero(&params, 4 * MAX_PARAMS);
	params_size = get_param(mem, *pc + 1, op, params);
	mem[*pc + params[1]]

	*pc += params_size + 1;
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
