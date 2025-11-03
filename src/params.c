/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:02:29 by amonot            #+#    #+#             */
/*   Updated: 2025/11/03 19:33:03 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int param_val(t_params params, int n)
{
	int val;
	unsigned char tmp[4];

	if (params.size[n] == 1) {
		val = params.tab[n][0];
	} else if (params.size[n] == 2){
		rv_memcpy(tmp, params.tab[n], 2);
		val = *(short int *)tmp;
	} else {
		rv_memcpy(tmp, params.tab[n], 4);
		val = *(int *)tmp;
	}
	return (val);
}

// return little
// unsigned char	*param_sub_val(unsigned char mem[MEM_SIZE], unsigned char reg[REG_NUMBER][REG_SIZE], t_params params, int n)
// {
// 	int p_val;
// 	static unsigned char sub_val[4];
// 	int tmp;
	

// 	p_val = param_val(params, n);
// 	if (params.types[n] == DIR_CODE)
// 		ft_memcpy(sub_val, p_val, 4);
// 	else if (params.types[n] == REG_CODE)
// 	{
// 		if (reg_access(reg, p_val) == NULL)
// 			return (NULL);
// 		rv_memcpy(sub_val, reg_access(reg, p_val), 4);
// 	}
// 	else
// 	{
// 		mem_cpy(mem, p_val, &tmp, 4);
// 		rv_memcpy(sub_val, tmp, 4);
// 	}
// 	return (sub_val);
// }
