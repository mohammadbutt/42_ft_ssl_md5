/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_md5_table_s.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:05:01 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/12 14:08:28 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	compute_md5_table_s_0_to_31(uint32_t *num)
{
	int i;

	i = 0;
	while (i >= 0 && i <= 15)
	{
		num[i++] = 7;
		num[i++] = 12;
		num[i++] = 17;
		num[i++] = 22;
	}
	while (i >= 16 && i <= 31)
	{
		num[i++] = 5;
		num[i++] = 9;
		num[i++] = 14;
		num[i++] = 20;
	}
}

void	compute_md5_table_s_32_to_63(uint32_t *num)
{
	int i;

	i = 32;
	while (i >= 32 && i <= 47)
	{
		num[i++] = 4;
		num[i++] = 11;
		num[i++] = 16;
		num[i++] = 23;
	}
	while (i >= 48 && i <= 63)
	{
		num[i++] = 6;
		num[i++] = 10;
		num[i++] = 15;
		num[i++] = 21;
	}
}

/*
** s specifies the pre round shift amount
** compute_table_functions:
** compute_md5_table_s ✓
** compute_md5_table_k ✓
** compute_md5_table_m, g_md5_table_m -> in header ✓
** compute_md5_table_padding ✓
*/

void	compute_md5_table_s(uint32_t *num)
{
	ft_bzero(num, (64 * 4));
	compute_md5_table_s_0_to_31(num);
	compute_md5_table_s_32_to_63(num);
}
