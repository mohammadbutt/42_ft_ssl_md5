/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:17:55 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/04 16:19:26 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned char	*memory;
	size_t			i;

	i = 0;
	memory = malloc(sizeof(unsigned char) * (size));
	if(memory == NULL || size > SIZE_T_MAX)
		return (NULL);
	else
		while (i <= size)
			memory[i++] = 0;
	return (memory);
}
