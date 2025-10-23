/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:45:07 by amonot            #+#    #+#             */
/*   Updated: 2025/10/22 18:08:02 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void creat_process(t_champion champion, unsigned char mem[MEM_SIZE])
{
	t_process	*process;
	t_process	*last_born;
	int			p;

	p = 1;
	process = NULL;
	last_born = new_process(champion.ids[0], 0 * (MEM_SIZE / champion.nbr));
	if (last_born == NULL)
	{
		perror("new_process");
		return ;
	}
	process = last_born;
	while (p < champion.nbr)
	{
		last_born = new_process(champion.ids[p], p * (MEM_SIZE / champion.nbr));
		if (last_born == NULL)
		{
			perror("new_process");
			break;
		}
		last_born->next = process;
		process = last_born;
		p++;
	}

	// p = 0;
	// while (p < champion.nbr)
	// {
	// 	int r;

	// 	rv_memcpy(&r, &process->reg[0], 4);
	// 	printf("process r1: %d\n", r);
	// 	process = process->next;
	// 	p++;
	// }
	//(void)mem;
	exec_process(champion, last_born, mem);
	//free_process(last_born); // ne marche pas
}
