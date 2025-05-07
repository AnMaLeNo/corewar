/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:54:11 by amonot            #+#    #+#             */
/*   Updated: 2025/05/07 15:54:32 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

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
