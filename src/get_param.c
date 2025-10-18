/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:54:11 by amonot            #+#    #+#             */
/*   Updated: 2025/10/16 17:31:49 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int param_size(t_op op, unsigned char acb, int n, int *type)
{
	if (op.has_pcode)
	{
		*type = (acb & 0b11000000 >> 2 * n) >> (6 - n * 2);
		if (*type == REG_CODE)
			return (PARAM_REGISTER);
		else if (*type == DIR_CODE)
			return (PARAM_DIRECT / (1 + op.has_idx));
		else if (*type == IND_CODE)
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

int get_param(unsigned char mem[MEM_SIZE], size_t pc, t_op op, t_params *params)
{
	unsigned char	acb;
	int				size;
	int				i;
	int				p_size;

	i = 0;
	size = 0;
	acb = mem[(pc + size) % MEM_SIZE]; // pc est = a pc + 1 en realiter
	if (op.has_pcode)
		size++;
	while (i < op.nb_params)
	{
		p_size = param_size(op, acb, i, &params->types[i]);
		//printf("param: %d, size: %d\n", i + 1, p_size);
		rv_memcpy(&params->tab[i], &mem[(pc + size) % MEM_SIZE], p_size);
		size += p_size;
		i++;
	}
	return (size);
}
