/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:54:11 by amonot            #+#    #+#             */
/*   Updated: 2025/11/03 18:54:33 by amonot           ###   ########.fr       */
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
			return (PARAM_DIRECT / 2); // 
		else
			return (op.param_types[n]);
	}
}

int get_param(unsigned char mem[MEM_SIZE], size_t pc, t_op op, t_params *params)
{
	unsigned char	acb;
	int			size;
	int			i;

	i = 0;
	size = 0;
	//acb = mem[(pc + 1) % MEM_SIZE]; // + 1 pour opcode // metre mem cpy !
	mem_cpy(mem, pc + 1, &acb, 1);
	if (op.has_pcode)
		size++;
	while (i < op.nb_params)
	{
		params->size[i] = param_size(op, acb, i, &params->types[i]);
		//rv_memcpy(&params->tab[i], &mem[(pc + size) % MEM_SIZE], params->size[i]); // pour quoi rv ?? il faut utiliser mem_cpy !
		mem_cpy(mem, pc + 1 + size, &params->tab[i], params->size[i]); // + 1 pour opcode
		size += params->size[i];
		i++;
	}
	return (size);
}
