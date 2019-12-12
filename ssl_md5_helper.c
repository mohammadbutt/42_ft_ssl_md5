/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_md5_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:11:08 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/12 14:13:41 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** rotate_left rotates x by n bits for md5
*/

uint32_t	rotate_left_32bit(uint32_t value, uint32_t rotate_n_bits)
{
	uint32_t	new_value;

	new_value = ((value << rotate_n_bits) | (value >> (32 - rotate_n_bits)));
	return (new_value);
}

void		ft_md5_print(t_ssl *ssl, char character)
{
	ft_printf("%08x%08x%08x", ssl->md5.a0, ssl->md5.b0, ssl->md5.c0);
	ft_printf("%08x%c", ssl->md5.d0, character);
}
