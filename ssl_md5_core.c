/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_md5_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:15:34 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/12 14:23:34 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	md5_function_fghi(uint32_t j, uint32_t b, uint32_t c, uint32_t d)
{
	uint32_t	f;
	uint32_t	g;
	uint32_t	h;
	uint32_t	i;

	zero_four_variables(&f, &g, &h, &i);
	if (j >= 0 && j <= 15)
		return (f = (b & c) | ((~b) & d));
	else if (j >= 16 && j <= 31)
		return (g = (d & b) | ((~d) & c));
	else if (j >= 32 && j <= 47)
		return (h = (b ^ c ^ d));
	else if (j >= 48 && j <= 63)
		return (i = c ^ (b | (~d)));
	return (0);
}

/*
** md5_update_state_abcd initializes and updates values to be used in the while
** loop.
** Values mapped based on wiki page.
** ssl->md5.a = A of wiki
** ssl->md5.b = B of wiki
** ssl->md5.c = C of wiki
** ssl->md5.d = D of wiki
**
** ssl->md5.a0 = a0 of wiki
** ssl->md5.b0 = b0 of wiki
** ssl->md5.c0 = c0 of wiki
** ssl->md5.d0 = d0 of wiki
*/

void		ft_update_md5_abcd(t_ssl *ssl)
{
	ssl->md5.a = ssl->md5.a0;
	ssl->md5.b = ssl->md5.b0;
	ssl->md5.c = ssl->md5.c0;
	ssl->md5.d = ssl->md5.d0;
}

void		swap_md5_adc_with_dcb(t_ssl *ssl)
{
	ssl->md5.a = ssl->md5.d;
	ssl->md5.d = ssl->md5.c;
	ssl->md5.c = ssl->md5.b;
}

/*
** Adds the newly retrieved values of a, b, c, d to ssl->md5.a0, ssl->md5.b0,
** ssl->md5.c0, and ssl->md5.d0
*/

void		ft_add_md5_abcd_to_a0b0c0d0(t_ssl *ssl)
{
	ssl->md5.a0 = ssl->md5.a0 + ssl->md5.a;
	ssl->md5.b0 = ssl->md5.b0 + ssl->md5.b;
	ssl->md5.c0 = ssl->md5.c0 + ssl->md5.c;
	ssl->md5.d0 = ssl->md5.d0 + ssl->md5.d;
}

void		swap_bits_to_fix_endian(t_ssl *ssl)
{
	ssl->md5.a0 = ft_swap_32bit(ssl->md5.a0);
	ssl->md5.b0 = ft_swap_32bit(ssl->md5.b0);
	ssl->md5.c0 = ft_swap_32bit(ssl->md5.c0);
	ssl->md5.d0 = ft_swap_32bit(ssl->md5.d0);
}
