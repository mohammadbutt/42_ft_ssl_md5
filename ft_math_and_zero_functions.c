/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_and_zero_functions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 19:03:40 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/12 19:13:52 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		ft_initialize_ssl_flag(t_ssl *ssl)
{
	ft_bzero(&ssl->flag, sizeof(ssl->flag));
	ft_bzero(&ssl->skip, sizeof(ssl->skip));
}

void		zero_four_variables(uint32_t *a, uint32_t *b, uint32_t *c,
		uint32_t *d)
{
	*a = 0;
	*b = 0;
	*c = 0;
	*d = 0;
}

void		zero_three_variables(uint32_t *a, uint32_t *b, uint32_t *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

uint64_t	ft_pow(int base, int exponent)
{
	uint64_t	total;
	int			i;

	total = base;
	i = 1;
	while (i < exponent)
	{
		total = total * base;
		i++;
	}
	return (total);
}

/*
** ft_fabs is used to convert negative floating point values into positive.
**
** Note: Has to be double, data type cannot be float because absolute value will
** be different if the data type is float instead of double.
** ft_fabs is used in md5 to compute a table.
*/

double		ft_fabs(double num)
{
	if (num < 0)
		num = -1 * num;
	return (num);
}
