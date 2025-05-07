/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:27:29 by amonot            #+#    #+#             */
/*   Updated: 2025/05/07 14:27:46 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int check_winner(t_vm *vm, t_champion champion)
{
	int i;
	int p;
	int num;

	i = 0;
	p = 0;
	while (i < champion.nbr)
	{
		printf("champion.ids[i]: %d\tchampion.live[i]: %ld\n", champion.ids[i], champion.live[i]);
		if (champion.ids[i] != -1 && champion.live[i] != 0)
		{
			num = champion.ids[i];
			p++;
		}
		i++;
	}
	if (p == 1)
	{
		vm->winner = num;
		return (1);
	}
	else if (p == 0)
	{
		vm->winner = -42;
		return (1);
	}
	return (0);
}

int check_live(t_vm *vm, t_champion champion)
{
	int i;

	i = 0;
	while (i < champion.nbr)
	{
		if (check_winner(vm, champion))
			return (1);
		if (vm->cycle - champion.live[i] >= vm->cycle_to_die)
		{
			if (champion.ids[i] >= 0)
			{
				printf("champion: %d die\n", champion.ids[i]);
				champion.ids[i] = -1;
			}
		}
		i++;
	}
	return (check_winner(vm, champion));
}

int check(t_vm *vm, t_champion champion)
{
	if (vm->last_check + vm->cycle_to_die < vm->cycle)
	{
		vm->last_check = vm->cycle; // ???
		if (check_live(vm, champion))
			return (1);
		vm->nb_check++;
		if (vm->nb_live >= NBR_LIVE)
		{
			vm->cycle_to_die -= CYCLE_DELTA;
			vm->nb_check = 0;	
		}
		else if (vm->nb_check == MAX_CHECKS)
		{
			vm->cycle_to_die -= CYCLE_DELTA;
			vm->nb_check = 0;
		}
	}
	return (0);
}