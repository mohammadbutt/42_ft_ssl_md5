/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 18:03:18 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/29 18:05:10 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_libft.h"

/*
** Prints a number in binary with spaces after 8 bits.
*/

char	*ft_binary(uint_fast64_t value, int base, char str[])
{
	int				len;
	uint_fast64_t	u_value;
	int				i;

	i = 0;
	len = 71;
	u_value = (uint_fast64_t)value;
	while(i < len)
	{
		((i + 1) % 9 == 0 && (i+1) != len && i != 0) && (str[i] = ' ');
		((i + 1) % 9 != 0) && (str[i] = '0');
		i++;
	}
	str[i--] = '\0';
	while(base && u_value)
	{
		if(str[i] == '0')
		{
			str[i] = u_value % base + '0';
			u_value = u_value / base;
		}
		i--;
	}
	return(str);
}
