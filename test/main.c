/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonot <amonot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:21:25 by amonot            #+#    #+#             */
/*   Updated: 2025/05/05 19:40:58 by amonot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

/* void * rv_memcpy(void *destination, const void *source, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = size - 1;
	while (i < size)
	{
		((char *)destination)[i] = ((const char *)source)[j];
		i++;
		j--;
	}
	return (destination);
} */

void put_int(char *mem, int n)
{
	int				masque = 0xFF000000;
	int				i;

	i = 0;
	while (i < 4)
	{
		mem[i] = (n & masque) >> (3 - i) * 8;
		masque = masque >> 8;
		i++;
	}
}

int read_int(char *mem)
{
	unsigned int n;
	int i;

	i = 0;
	n = 0;
	while (i < 4)
	{
		n << 8;
		n += mem[i];
		i++;
	}
	return (n);
}

int main(void)
{
 	int				n = 42;
 	unsigned char	mem[4];
/*  	int				rn = 0;
 	int				masque = 0xFF000000;
 	int				i;

 	i = 0;
 	while (i < 4)
 	{
 		mem[i] = (n & masque) >> (3 - i) * 8;
 		masque = masque >> 8;
 		//printf("%X ", mem[i]);
 		i++;
 	} */
	put_int(mem, 42);
 	//ft_memcpy(&mem, &n, 4);
 	printf("mem[0]: %d\n", mem[0]);
 	printf("mem[1]: %d\n", mem[1]);
 	printf("mem[2]: %d\n", mem[2]);
 	printf("mem[3]: %d\n", mem[3]);
	printf("mem int: %d\n", read_int(mem));
 	//ft_memcpy(&rn, &mem, 4);
 	//printf("rn: %d\n", rn);
}

/* #include <stdio.h>

int main() {
    unsigned int x = 0x12345678; // Une valeur avec des octets distincts
    unsigned char *p = (unsigned char *)&x; // Pointeur vers les octets de x

    // Si le premier octet est 0x78, c'est little-endian
    // Si le premier octet est 0x12, c'est big-endian
    printf("Premier octet : 0x%02x\n", *p);
    if (*p == 0x78) {
        printf("Little-endian\n");
    } else if (*p == 0x12) {
        printf("Big-endian\n");
    } else {
        printf("Endianness inconnu ou erreur\n");
    }

    return 0;
} */