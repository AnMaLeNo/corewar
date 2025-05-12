/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:36:40 by amonot            #+#    #+#             */
/*   Updated: 2025/05/11 03:11:44 by amonot           ###   ########.fr       */
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
	int				cycle_to_die;
	unsigned int	nb_live;
	int				nb_check;
	int				winner;
}					t_vm;

typedef struct s_params
{
	int	tab[MAX_PARAMS];
	int	types[MAX_PARAMS];
}		t_params;

int get_header(int fd, t_header	*champion);
int get_champion(int argc, char *argv[], t_header champion[MAX_PLAYERS], unsigned char mem[MEM_SIZE]);
void creat_process(t_champion champion, unsigned char mem[MEM_SIZE]);
void exec_process(t_champion champion, t_process *process, unsigned char mem[MEM_SIZE]);
int check(t_vm *vm, t_champion champion);
int exec_instruction(unsigned char mem[MEM_SIZE], t_process *process);
int get_param(unsigned char mem[MEM_SIZE], size_t pc, t_op op, t_params *params);
t_process *new_process(int num, unsigned long int pc);
void free_process(t_process *process);

// instruction
int live(unsigned char mem[MEM_SIZE], size_t *pc);
void ld(unsigned char mem[MEM_SIZE], t_process *process, t_op op);
void st(unsigned char mem[MEM_SIZE], t_process *process, t_op op);
void add(unsigned char mem[MEM_SIZE], t_process *process, t_op op);
void zjmp(unsigned char mem[MEM_SIZE], t_process *process, t_op op);


// utile
void	ft_bzero(void *s, size_t n);
void	*rv_memcpy(void *destination, const void *source, size_t size);
int		ft_strcmp(const char *first, const char *second);
void	*rv_memcpy(void *destination, const void *source, size_t size);
void	*ft_memcpy(void *destination, const void *source, size_t size);

// debug
void debug(unsigned char mem[MEM_SIZE], t_vm vm, t_process *process);

#endif
