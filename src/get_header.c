/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:36:08 by amonot            #+#    #+#             */
/*   Updated: 2025/10/20 17:12:27 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int get_int(int fd, unsigned int *nbr)
{
	unsigned long int	i;
	unsigned char		buf;
	int					r;

	i = 0;
	r = 1;
	*nbr = 0;
	buf = 0;
	while (i < 4 && r == 1) // pas sur que (r ==1) sert a quel que chose
	{
		r = read(fd, &buf, 1); // fair dans l'autre sans pour read 
		if (r == -1)
			return (-1);
		*nbr = *nbr << 8;
		*nbr += buf;
		i++;
	}
	return (0);
}

int get_str(int fd, char *str, unsigned int size)
{
	unsigned int	i;
	unsigned char		buf;
	int					r;

	i = 0;
	r = 1;
	while (i < size && r == 1)
	{
		r = read(fd, &buf, 1);
		if (r == -1)
			return (-1);
		str[i] = buf;
		i++;
		if (buf == 0)
			break;
	}
	while (i < size + 4 && r == 1) // Pour le Séparateur nul de 4 octets à 0x00
	{
		r = read(fd, &buf, 1);
		i++;
	}
	if (i != size + 4)
	{
		printf("error in get_str i: %d\n", i);
		return (-1);
	}
	return (0);
}

int get_header(int fd, t_header	*champion)
{
	if (get_int(fd, &champion->magic))
	{
		write(2, "is not a corewar executable.\n", 29);
		return (-100);
	}
	if (champion->magic != COREWAR_EXEC_MAGIC)
	{
		write(2, "is not a corewar executable.\n", 29);
		return (-100);
	}
	if (get_str(fd, champion->prog_name, PROG_NAME_LENGTH))
	{
		perror("prog_name");
		return (-100);
	}
	if (get_int(fd, &champion->prog_size))
	{
		perror("prog_size");
		return (-100);
	}
	if (get_str(fd, champion->comment, COMMENT_LENGTH))
	{
		perror("comment");
		return (-100);
	}

	// printf("magic: %x\n", champion->magic);
	// printf("name: %s\n", champion->prog_name);
	// printf("prog_size: %d\n", champion->prog_size);
	// printf("comment: %s\n", champion->comment);
	// printf("----------------------------------------\n\n");
	return (0);
}