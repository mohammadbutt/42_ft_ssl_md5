/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_sha512_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:31:21 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/12 18:44:53 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	ft_update_sha512_abcdefgh(t_ssl *ssl)
{
	ssl->sha512.a = ssl->sha512.h0;
	ssl->sha512.b = ssl->sha512.h1;
	ssl->sha512.c = ssl->sha512.h2;
	ssl->sha512.d = ssl->sha512.h3;
	ssl->sha512.e = ssl->sha512.h4;
	ssl->sha512.f = ssl->sha512.h5;
	ssl->sha512.g = ssl->sha512.h6;
	ssl->sha512.h = ssl->sha512.h7;
}

void	ft_add_sha512_abcdefgh_to_h_values(t_ssl *ssl)
{
	ssl->sha512.h0 = ssl->sha512.h0 + ssl->sha512.a;
	ssl->sha512.h1 = ssl->sha512.h1 + ssl->sha512.b;
	ssl->sha512.h2 = ssl->sha512.h2 + ssl->sha512.c;
	ssl->sha512.h3 = ssl->sha512.h3 + ssl->sha512.d;
	ssl->sha512.h4 = ssl->sha512.h4 + ssl->sha512.e;
	ssl->sha512.h5 = ssl->sha512.h5 + ssl->sha512.f;
	ssl->sha512.h6 = ssl->sha512.h6 + ssl->sha512.g;
	ssl->sha512.h7 = ssl->sha512.h7 + ssl->sha512.h;
}

void	ft_sha512_swap_abcdefgh(t_ssl *ssl)
{
	ssl->sha512.h = ssl->sha512.g;
	ssl->sha512.g = ssl->sha512.f;
	ssl->sha512.f = ssl->sha512.e;
	ssl->sha512.e = ssl->sha512.d + ssl->sha512.temp1;
	ssl->sha512.d = ssl->sha512.c;
	ssl->sha512.c = ssl->sha512.b;
	ssl->sha512.b = ssl->sha512.a;
	ssl->sha512.a = ssl->sha512.temp1 + ssl->sha512.temp2;
}

/*
** 120 bytes is allocated on stack for ssl->sha512.table_w because messages for
** sha512 and sha384 get processed in 1024 chunks.
** 128 bytes * 8 = 1024;
** Allocating space for 128 characters for w is different then going through 80
** rounds to get the new value of w each time.
*/

void	ft_sha512_process_1024bit_chunk(t_ssl *ssl, uint64_t chunk)
{
	uint64_t i;
	uint64_t *w;
	uint64_t *padded_message;

	i = 16;
	w = ssl->sha512.table_w;
	padded_message = ssl->sha512.padded_message;
	ft_bzero_num_array_64bit(w, 128);
	ft_memcpy(w, padded_message + (16 * chunk), 128);
	while (i < 80)
	{
		ssl->sha512.s0 = rotate_right_64bit(w[i - 15], 1) ^\
							rotate_right_64bit(w[i - 15], 8) ^\
							shift_right_64bit(w[i - 15], 7);
		ssl->sha512.s1 = rotate_right_64bit(w[i - 2], 19) ^\
							rotate_right_64bit(w[i - 2], 61) ^\
							shift_right_64bit(w[i - 2], 6);
		w[i] = w[i - 16] + ssl->sha512.s0 + w[i - 7] + ssl->sha512.s1;
		i++;
	}
}

void	ft_sha512_compression(t_ssl *ssl)
{
	uint32_t i;

	i = 0;
	ft_update_sha512_abcdefgh(ssl);
	while (i < 80)
	{
		ssl->sha512.ss1 = rotate_right_64bit(ssl->sha512.e, 14) ^ \
							rotate_right_64bit(ssl->sha512.e, 18) ^ \
							rotate_right_64bit(ssl->sha512.e, 41);
		ssl->sha512.ch = (ssl->sha512.e & ssl->sha512.f) ^\
							((~ssl->sha512.e) & ssl->sha512.g);
		ssl->sha512.temp1 = ssl->sha512.h + ssl->sha512.ss1 + ssl->sha512.ch +\
							g_sha512_table_k[i] + ssl->sha512.table_w[i];
		ssl->sha512.ss0 = rotate_right_64bit(ssl->sha512.a, 28) ^\
							rotate_right_64bit(ssl->sha512.a, 34) ^\
							rotate_right_64bit(ssl->sha512.a, 39);
		ssl->sha512.maj = (ssl->sha512.a & ssl->sha512.b) ^\
							(ssl->sha512.a & ssl->sha512.c) ^\
							(ssl->sha512.b & ssl->sha512.c);
		ssl->sha512.temp2 = ssl->sha512.ss0 + ssl->sha512.maj;
		ft_sha512_swap_abcdefgh(ssl);
		i++;
	}
	ft_add_sha512_abcdefgh_to_h_values(ssl);
}
