/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:21:25 by amonot            #+#    #+#             */
/*   Updated: 2025/05/04 21:58:20 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void * ft_memcpy(void *destination, const void *source, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		((char *)destination)[i] = ((const char *)source)[i];
		i++;
	}
	return (destination);
}

int main(void)
{
	int				n = 1431655765;
	unsigned char	mem[4];
	int				masque = 0xFF000000;
	int				i;

	i = 0;
	while (i < 4)
	{
		mem[i] = (n & masque) >> (3 - i) * 8;
		masque = masque >> 8;
		printf("%X ", mem[i]);
		i++;
	}
}