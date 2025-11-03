/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:02:29 by amonot            #+#    #+#             */
/*   Updated: 2025/11/03 18:51:37 by amonot           ###   ########.fr       */
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

// int	param_sub_val(unsigned char mem[MEM_SIZE], t_params params, int n)
// {
// 	int p_val;
// 	int sub_val;
	

// 	p_val = param_val(params, n);
// 	if (params.types[n] == DIR_CODE)
// 		sub_val = p_val;
// 	if (params.types[n] == IND_CODE)
// 		mem_cpy(mem, p_val, &sub_val, 4);
// 	else if ()

// 	return (sub_val)
// }