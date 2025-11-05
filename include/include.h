/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:36:40 by amonot            #+#    #+#             */
/*   Updated: 2025/11/05 14:27:59 by amonot           ###   ########.fr       */
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

// pc: le byte le moins significatif en premier
// corwar: le byte le plus significatif en premier

typedef struct s_process
{
	unsigned char			reg[REG_NUMBER][REG_SIZE]; // reg c'est les registre // !! char -> unsigned char
	size_t				pc; // l’adresse du prochain ensemble d’instructions à exécuter
	bool				carry; // un flage que certaine opérations peuvent modifier
	int					cycle; // ?? (nombre de cyle a attendre avant d'executer la prochenne instruction)
	struct s_process	*next;
}						t_process;

typedef struct s_champion
{
	int			nbr; // nombre de champion
	t_header	header[MAX_PLAYERS]; // le header des champion
	int			ids[MAX_PLAYERS]; // les id/num des champion
	size_t		live[MAX_PLAYERS]; // numero du cycle du dernier live
}				t_champion;

typedef struct s_vm
{
	size_t			cycle; // 1 cycle = 1 tick de la vm 
	size_t			last_check;
	t_process		*last_born; // liste chainee des processus
	int				cycle_to_die; // Tous les CYCLE_TO_DIE cycles, la machine doit vérifier que chaque processus a exécuté au moins une instruction live depuis la dernière vérification
	unsigned int	nb_live; // nombre total d’instructions live exécutées toutes confondues
	int				nb_check; // nombre de "cycle_to_die" survecue sans que personne meur
	int				winner;
}					t_vm;

typedef struct s_params
{
	unsigned char	tab[MAX_PARAMS][DIR_SIZE]; // int -> unsigned char *
	int			types[MAX_PARAMS];
	int			size[MAX_PARAMS];
}				t_params;

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
void sub(unsigned char mem[MEM_SIZE], t_process *process, t_op op);
void and(unsigned char mem[MEM_SIZE], t_process *process, t_op op);
void or(unsigned char mem[MEM_SIZE], t_process *process, t_op op);
void xor(unsigned char mem[MEM_SIZE], t_process *process, t_op op);
void zjmp(unsigned char mem[MEM_SIZE], t_process *process, t_op op);


// utile
void			ft_bzero(void *s, size_t n);
void			*rv_memcpy(void *destination, const void *source, size_t size);
int			ft_strcmp(const char *first, const char *second);
void			*ft_memcpy(void *destination, const void *source, size_t size);
void			mem_set(unsigned char mem[MEM_SIZE], ssize_t start, const void *src,  int size);
void			mem_cpy(unsigned char mem[MEM_SIZE], ssize_t start, const void *dest, int size);
void			*endian_convert(void *data, unsigned int n);

// registries
void reg_set(unsigned char	reg[REG_NUMBER][REG_SIZE], int r, void *src);
unsigned char *reg_access(unsigned char	reg[REG_NUMBER][REG_SIZE], int r);
bool is_valid_reg(t_params params, t_op op);

// params
int param_val(t_params params, int n);
int	param_sub_val(unsigned char mem[MEM_SIZE], unsigned char reg[REG_NUMBER][REG_SIZE], t_params params, int n);

// debug
void debug(unsigned char mem[MEM_SIZE], t_vm vm, t_process *process);
void print_params(t_params param, int n);

#endif
