/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:11:26 by amonot            #+#    #+#             */
/*   Updated: 2025/05/04 21:07:32 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "include.h"

void dump_mem(unsigned char mem[MEM_SIZE])
{
	unsigned long int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		printf("%X ", mem[i]);
		i++;
	}
}

void	init_mem(unsigned char mem[MEM_SIZE])
{
	unsigned long int i;

	i = 0;
	while (i < MEM_SIZE)
		mem[i++] = 0;
}

void set_champions_num(int ch_num[MAX_PLAYERS])
{
	int	p;

	p = 0;
	while (p < MAX_PLAYERS)
	{
		ch_num[p] = p + 1;
		p++;
	}
}

int main(int argc, char *argv[])
{
	unsigned char 		mem[MEM_SIZE];
	t_header			champion[MAX_PLAYERS];
	int					ch_num[MAX_PLAYERS];
	int					nbr;

	init_mem(mem);
	set_champions_num(ch_num);
	nbr = get_champion(argc, argv, champion, mem);
	if (nbr == -1)
		perror("get_champion");
	else if (nbr == -2)
		write(2, "too many players\n", 17);
	else if (nbr == -3)
		write(2, "prog_size not the same\n", 17);
	else if (nbr >= 0)
	{
		printf("nombre de champion: %d\n", nbr);
		dump_mem(mem);
		creat_process(champion, nbr, ch_num);
	}
}
