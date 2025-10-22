/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_champion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:36:01 by amonot            #+#    #+#             */
/*   Updated: 2025/10/22 16:44:51 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int load_champion(int *fd, unsigned char mem[MEM_SIZE], int nbr, t_header champion[MAX_PLAYERS])
{
	unsigned long int	i;
	unsigned char		buf;
	int					p;
	int					r;

	p = 0;
	r = 1; // ca sert a rien
	while (p < nbr)
	{
		i = p * (MEM_SIZE / nbr);
		r = read(fd[p], &buf, 1);
		while (r == 1)
		{
			mem[i % MEM_SIZE] = buf;
			r = read(fd[p], &buf, 1);
			i++;
		}
		if (r == -1)
			return (-1);
		if (champion[p].prog_size != i - (p * (MEM_SIZE / nbr)))
			return (-3);
		p++;
	}
	//close fd ici ?
	return (nbr);
}

int get_champion(int argc, char *argv[], t_header champion[MAX_PLAYERS], unsigned char mem[MEM_SIZE])
{
	int i;
	int p;
	int fd[MAX_PLAYERS]; // close ?

	i = 1;
	p = 0;
	while (i < argc)
	{
		if (p >= MAX_PLAYERS)
			return (-2);
		fd[p] = open(argv[i], O_RDONLY);
		if (fd[p] == -1)
		{
			while (--p >= 0)
				close(fd[p]);
			return (-1);
		}
		if (get_header(fd[p], &champion[p]) != 0)
			return (-100);
		i++;
		p++;
	}
	return (load_champion(fd , mem, p, champion));
}
