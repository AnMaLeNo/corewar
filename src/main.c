/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:11:26 by amonot            #+#    #+#             */
/*   Updated: 2025/10/20 17:25:41 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "include.h"

void dump_mem(unsigned char mem[MEM_SIZE])
{
	unsigned long int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		printf("%X\t", mem[i]);
		i++;
		if (i % (16 * 4) == 0)
			break;
		if (i % 16 == 0)
			printf("\n");
	}
	printf("\n");
}

void ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
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
	t_champion			champion;

	ft_bzero(&champion, sizeof(t_champion));
	ft_bzero(mem, MEM_SIZE);
	set_champions_num(champion.ids); // mes des numero pour tout les place de champion disponible
	//ft_bzero(champion.live, sizeof(unsigned int) * MAX_PLAYERS); // ?? (pour quoi est ce qu'il est commanter)
	champion.nbr = get_champion(argc, argv, champion.header, mem);
	if (champion.nbr == -1)
		perror("get_champion");
	else if (champion.nbr == -2)
		write(2, "Too many players\n", 17);
	else if (champion.nbr == -3)
		write(2, "prog_size not the same\n", 23);
	else if (champion.nbr >= 0)
	{
		printf("Nombre de champion: %d\n", champion.nbr);
		//dump_mem(mem);
		creat_process(champion, mem);
		//dump_mem(mem);
	}
}
