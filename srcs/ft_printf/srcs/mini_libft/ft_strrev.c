/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 21:09:16 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/11 19:29:44 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_libft.h"

/*
** function ft_strrev takes a string and reverses it in place
*/

char	*ft_strrev(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str) - 1;
	if (str)
		while (i < len)
			ft_swap(&str[i++], &str[len--]);
	return (str);
}
