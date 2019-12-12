/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:16:22 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/11 19:39:47 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_libft.h"

/*
** Allocates memory to hold string 1 and string 2 and then joins the two to and
** returns the address of the new string/ new pointer.
** Output string gets joined / concatenated in the following manner:
** str1 = "This"
** str2 = "Test"
** final_string = str1 + str2;
** final_string = "ThisTest"
**
** Note: ft_strjoin is different from ft_strcat. Because ft_strjoin returns a
** new pointer, but ft_strcat does not return a new pointer.
*/

char	*ft_strjoin(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*final_str;

	if (str1 == NULL || str2 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	final_str = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (final_str == NULL)
		return (NULL);
	while (str1[j])
		final_str[i++] = str1[j++];
	j = 0;
	while (str2[j])
		final_str[i++] = str2[j++];
	final_str[i] = '\0';
	return (final_str);
}
