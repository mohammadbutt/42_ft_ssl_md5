/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:17:55 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/11 19:33:17 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_libft.h"

/*
** Does the following three things.
** 1. Allocated memory.
** 2. Checks if memory was successfully allocated to prevent the program from
** crashing.
** 3. bzero the memory that was allocated to ensure that the allocated memory
** is clean and there are no garbage values.
*/

void	*ft_memalloc(size_t size)
{
	unsigned char	*memory;
	size_t			i;

	i = 0;
	memory = malloc(sizeof(unsigned char) * (size));
	if (memory == NULL || size > SIZE_T_MAX)
		return (NULL);
	else
		while (i <= size)
			memory[i++] = 0;
	return (memory);
}
