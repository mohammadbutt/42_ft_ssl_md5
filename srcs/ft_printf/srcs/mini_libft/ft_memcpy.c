/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:06:33 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/08 15:34:13 by mbutt            ###   ########.fr       */
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

void *ft_memcpy(void *dst0, const void *src0, size_t len)
{
	size_t i;
	unsigned char *dest;
	unsigned char *source;

	i = 0;
	dest = (unsigned char *)dst0;
	source = (unsigned char *)src0;
	while(i < len)
	{
		dest[i] = source[i];
		i++;
	}
	return((void *)dst0);
}

/*
void *ft_memcpy(void *dst0, const void *srce0, int len)
{
	int i;
	int j;
	unsigned char *source;
	unsigned char *dest;

	i = 0;
	j = 0;
	source = (unsigned char *)srce0;
	dest = (unsigned char *)dst0;
	while(i < len)
	{
		if(source[j] != '\0')
			dest[i] = source[j++];
		else
			dest[i] = 0;
		i++;
	}
	return(dst0);
}
*/
/*
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
		if(source)
			dest[i] = source[i];
		else
			dest[i] = 0;
		i++;
		n--;
	}
	return (original_dest);
}
*/
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
