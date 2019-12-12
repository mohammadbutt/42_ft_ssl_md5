/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:06:33 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/11 19:26:50 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_libft.h"

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

void	*ft_memcpy(void *dst0, const void *src0, size_t len)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*source;

	i = 0;
	dest = (unsigned char *)dst0;
	source = (unsigned char *)src0;
	while (i < len)
	{
		dest[i] = source[i];
		i++;
	}
	return ((void *)dst0);
}
