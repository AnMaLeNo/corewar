/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:21:25 by amonot            #+#    #+#             */
/*   Updated: 2025/05/11 02:32:18 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_test
{
	int	tab1[5];
	int *tab2;
}		t_test;

void init(t_test test)
{
	test.tab1[0] = 42;
	test.tab2[0] = 42;
	printf("init: tabe1[0]: %d\n", test.tab1[0]);
	printf("init: tabe2[0]: %d\n", test.tab2[0]);
}

int main(void)
{
	t_test test;

	test.tab1[0] = 0;
	test.tab2 = malloc(sizeof(int) * 5);
	test.tab2[0] = 0;
	init(test);
	printf("main: tabe1[0]: %d\n", test.tab1[0]);
	printf("main: tabe2[0]: %d\n", test.tab2[0]);
	return (0);
}