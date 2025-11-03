/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registries.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:04:01 by amonot            #+#    #+#             */
/*   Updated: 2025/11/03 19:31:54 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

// void reg_cpy(unsigned char	reg[REG_NUMBER][REG_SIZE], int r, void *dest)
// {
// 	int i;

// 	i = 0;
// 	if (r < 1 || r > REG_NUMBER)
// 		return ;
// 	while (i < REG_SIZE)
// 	{
// 		((unsigned char *)dest)[i] = reg[r - 1][i];
// 		i++;
// 	}
// }

void reg_set(unsigned char	reg[REG_NUMBER][REG_SIZE], int r, void *src)
{
	int i;

	i = 0;
	if (r < 1 || r > REG_NUMBER || src == NULL)
		return ;
	while (i < REG_SIZE)
	{
		reg[r - 1][i] = ((unsigned char *)src)[i];
		i++;
	}
}

unsigned char *reg_access(unsigned char	reg[REG_NUMBER][REG_SIZE], int r)
{
	if (r < 1 || r > REG_NUMBER)
		return (NULL);
	return (reg[r - 1]);
}

bool is_valid_reg(t_params params, t_op op)
{
	int 			i;

	i = 0;
	while (i < op.nb_params)
	{
		if (params.types[i] == REG_CODE)
		{
			if (param_val(params, i) < 1 || param_val(params, i) > 16)
				return (false);
		}
		i++;
	}
	return (true);
}