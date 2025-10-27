/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registries.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:04:01 by amonot            #+#    #+#             */
/*   Updated: 2025/10/27 17:16:40 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void reg_set(unsigned char	reg[REG_NUMBER][REG_SIZE], int r, void *dest)
{
	int i;

	i = 0;
	if (r < 1 || r > REG_NUMBER)
		return ;
	while (i < REG_SIZE)
	{
		((unsigned char *)dest)[i] = reg[r - 1][i];
		i++;
	}
}
