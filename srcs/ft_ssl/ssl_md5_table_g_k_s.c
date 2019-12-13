/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_md5_table_g_k_s.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:00:09 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/12 14:00:18 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** Formula from https://en.wikipedia.org/wiki/MD5
** if 0 ≤ i ≤ 15 then
** 		g := i
** else if 16 ≤ i ≤ 31 then
** 		g := (5×i + 1) mod 16
** else if 32 ≤ i ≤ 47 then
** 		g := (3×i + 5) mod 16
** else if 48 ≤ i ≤ 63 then
** 		g := (7×i) mod 16
**
** Note: Change name from compute_md5_table_x to compute_md5_table_g
*/

void	compute_md5_table_g(uint32_t *num)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	j = 0;
	while (j <= 15)
		num[i++] = j++;
	while (j <= 31)
		num[i++] = ((5 * j++) + 1) % 16;
	while (j <= 47)
		num[i++] = ((3 * j++) + 5) % 16;
	while (j <= 63)
		num[i++] = (7 * j++) % 16;
}

void	compute_md5_table_k(uint32_t *num)
{
	uint32_t	i;
	int			base;
	int			exponent;

	i = 0;
	base = 2;
	exponent = 32;
	ft_bzero(num, (64 * 4));
	while (i < 64)
	{
		num[i] = (uint32_t)(ft_pow(base, exponent) * ft_fabs(sin(i + 1)));
		i++;
	}
}

void	compute_md5_table_g_k_s(t_ssl *ssl)
{
	compute_md5_table_g(ssl->md5.table_g);
	compute_md5_table_k(ssl->md5.table_k);
	compute_md5_table_s(ssl->md5.table_s);
}
