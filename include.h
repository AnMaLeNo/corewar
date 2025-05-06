/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:36:40 by amonot            #+#    #+#             */
/*   Updated: 2025/05/06 19:15:01 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef INCLUDE_H
# define INCLUDE_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include "op.h"

#define MAX_PARAMS 4 

typedef struct s_process
{
	char				reg[REG_NUMBER][REG_SIZE];
	size_t				pc;
	bool				carry;
	int					cycle;
	struct s_process	*next;
}						t_process;

typedef struct s_champion
{
	int			nbr;
	t_header	header[MAX_PLAYERS];
	int			ids[MAX_PLAYERS];
	size_t		live[MAX_PLAYERS];
}				t_champion;

typedef struct s_vm
{
	size_t			cycle;
	size_t			last_check;
	t_process		*last_born;
	unsigned int	cycle_to_die;
	unsigned int	nb_live;
	int				nb_check;
	int				winner;
}					t_vm;

int get_header(int fd, t_header	*champion);
int get_champion(int argc, char *argv[], t_header champion[MAX_PLAYERS], unsigned char mem[MEM_SIZE]);
void creat_process(t_champion champion, unsigned char mem[MEM_SIZE]);
void exec_process(t_champion champion, t_process *process, unsigned char mem[MEM_SIZE]);

// utile
void	ft_bzero(void *s, size_t n);
void	*rv_memcpy(void *destination, const void *source, size_t size);
int		ft_strcmp(const char *first, const char *second);
void	*rv_memcpy(void *destination, const void *source, size_t size);

#endif
