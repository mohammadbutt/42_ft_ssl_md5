/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 15:50:22 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/11 19:35:04 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_libft.h"

/*
**int	ft_strlen(char *str)
**{
**	int i;
**
**	i = 0;
**	if(str)
**		while(str[i])
**			i++;
**	return(i);
**}
*/

int				ft_strlen(char *str)
{
	int_fast32_t i;

	i = 0;
	if (str)
		while (str[i])
		{
			if (str[i + 1] == '\0')
				return (i + 1);
			else if (str[i + 2] == '\0')
				return (i + 2);
			else
				i = i + 3;
		}
	return (i);
}

uint32_t		ft_strlen_uint32(char *str)
{
	uint32_t i;

	i = 0;
	if (str)
		while (str[i])
		{
			if (str[i + 1] == '\0')
				return (i + 1);
			else if (str[i + 2] == '\0')
				return (i + 2);
			else
				i = i + 3;
		}
	return (i);
}

uint64_t		ft_strlen_uint64(char *str)
{
	uint64_t i;

	i = 0;
	if (str)
		while (str[i])
		{
			if (str[i + 1] == '\0')
				return (i + 1);
			else if (str[i + 2] == '\0')
				return (i + 2);
			else
				i = i + 3;
		}
	return (i);
}

/*
** ft_strlen_fast inspired by one of the discussions I had with Eric.
** It is an experimental function and it is much faster than the regular
** ft_strlen.
*/

int_fast32_t	ft_strlen_fast(char *str)
{
	int_fast32_t i;

	i = 0;
	if (str)
		while (str[i])
		{
			if (str[i + 1] == '\0')
				return (i + 1);
			else if (str[i + 2] == '\0')
				return (i + 2);
			else
				i = i + 3;
		}
	return (i);
}
