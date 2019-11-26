/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:06:33 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/25 18:03:32 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_libft.h"
#include <stdio.h>
#include <string.h>
/*
** Memcpy vs strcpy. strcpy stops copying as soon as it comes across a null
** terminator, '\0'. But memcpy copies over n number of bytes.
** Which is also why there is no null termination in memcpy.
**
** It is helpful to print a string in a while loop character by character.
** 
** To ensure that a string is properly null terminated, bzero should be
** performed on destination and source string and then memcpy should be
** performed.
*/

void *ft_memcpy(void *original_dest, const void *original_source, size_t n)
{
	char		*dest;
	const char	*source;
	size_t		i;

	dest = original_dest;
	source = original_source;
	i = 0;
	while (n)
	{
		dest[i] = source[i];
		i++;
		n--;
	}
	return (original_dest);
}

/*
int main(void)
{
	char *str1;
	char *str2;

	str1 = malloc(sizeof(char) * (16));
	str2 = malloc(sizeof(char) * (16));

//	ft_bzero(str1, sizeof(str1));
	ft_bzero(str2, sizeof(str2));
	ft_strcpy(str1, "ABC");
	ft_strcpy(str2, "abcd");

//	memcpy(str1, str2, 3);
//	ft_bzero(str1, 16);
	ft_memcpy(str1, str2, 16);
	printf("memcpy:|%s|\n", str1);

	int i = 0;
	while(i < 12)
		printf("%c", str1[i++]);
}
*/
