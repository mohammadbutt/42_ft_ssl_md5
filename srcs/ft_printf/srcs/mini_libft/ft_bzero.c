/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 17:52:38 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/08 18:52:13 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_libft.h"

void	ft_bzero(void *s, size_t len)
{
	unsigned char	*str;
	size_t			i;

	str = s;
	i = 0;
	while (i < len)
		str[i++] = 0;
}

/*
** function ft_bten is created to test structs that have a lot of members
** ft_bten is created to set values to something other than zero to test if
** the method used in ft_bzero will be effective or not.
*/

void	ft_bten(void *s, size_t len)
{
	unsigned char	*str;
	size_t 			i;

	str = s;
	i = 0;
	while(i < len)
		str[i++] = 10;
}

/*
** I have conducted some tests on ft_bzero_no_len and they passed.
** But it could be dangerous to run ft_bzero_no_len without explicitly passing
** in the size/length of the string.
*/

void	ft_bzero_no_len(void *s)
{
	unsigned char	*str;
	size_t			i;

	str = s;
	i = 0;
	if (str)
		while (str[i])
			str[i++] = 0;
}
