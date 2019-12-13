/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_sha256_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:58:23 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/12 16:23:37 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	ft_update_sha256_abcdefgh(t_ssl *ssl)
{
	ssl->sha256.a = ssl->sha256.h0;
	ssl->sha256.b = ssl->sha256.h1;
	ssl->sha256.c = ssl->sha256.h2;
	ssl->sha256.d = ssl->sha256.h3;
	ssl->sha256.e = ssl->sha256.h4;
	ssl->sha256.f = ssl->sha256.h5;
	ssl->sha256.g = ssl->sha256.h6;
	ssl->sha256.h = ssl->sha256.h7;
}

void	ft_add_sha256_abcdefgh_to_h_values(t_ssl *ssl)
{
	ssl->sha256.h0 = ssl->sha256.h0 + ssl->sha256.a;
	ssl->sha256.h1 = ssl->sha256.h1 + ssl->sha256.b;
	ssl->sha256.h2 = ssl->sha256.h2 + ssl->sha256.c;
	ssl->sha256.h3 = ssl->sha256.h3 + ssl->sha256.d;
	ssl->sha256.h4 = ssl->sha256.h4 + ssl->sha256.e;
	ssl->sha256.h5 = ssl->sha256.h5 + ssl->sha256.f;
	ssl->sha256.h6 = ssl->sha256.h6 + ssl->sha256.g;
	ssl->sha256.h7 = ssl->sha256.h7 + ssl->sha256.h;
}

void	ft_sha256_swap_abcdefgh(t_ssl *ssl)
{
	ssl->sha256.h = ssl->sha256.g;
	ssl->sha256.g = ssl->sha256.f;
	ssl->sha256.f = ssl->sha256.e;
	ssl->sha256.e = ssl->sha256.d + ssl->sha256.temp1;
	ssl->sha256.d = ssl->sha256.c;
	ssl->sha256.c = ssl->sha256.b;
	ssl->sha256.b = ssl->sha256.a;
	ssl->sha256.a = ssl->sha256.temp1 + ssl->sha256.temp2;
}

void	ft_sha256_process_512bit_chunk(t_ssl *ssl, uint32_t chunk)
{
	uint32_t	i;
	uint32_t	*w;
	uint32_t	*padded_message;

	i = 16;
	w = ssl->sha256.table_w;
	padded_message = ssl->sha256.padded_message;
	ft_bzero_num_array_32bit(w, 64);
	ft_memcpy(w, padded_message + (16 * chunk), 64);
	while (i < 64)
	{
		ssl->sha256.s0 = rotate_right_32bit(w[i - 15], 7) ^\
						rotate_right_32bit(w[i - 15], 18) ^\
						shift_right_32bit(w[i - 15], 3);
		ssl->sha256.s1 = rotate_right_32bit(w[i - 2], 17) ^\
						rotate_right_32bit(w[i - 2], 19) ^\
						shift_right_32bit(w[i - 2], 10);
		w[i] = w[i - 16] + ssl->sha256.s0 + w[i - 7] + ssl->sha256.s1;
		i++;
	}
}

void	ft_sha256_compression(t_ssl *ssl)
{
	uint32_t i;

	i = 0;
	ft_update_sha256_abcdefgh(ssl);
	while (i < 64)
	{
		ssl->sha256.ss1 = rotate_right_32bit(ssl->sha256.e, 6) ^\
							rotate_right_32bit(ssl->sha256.e, 11) ^\
							rotate_right_32bit(ssl->sha256.e, 25);
		ssl->sha256.ch = (ssl->sha256.e & ssl->sha256.f) ^\
							((~ssl->sha256.e) & ssl->sha256.g);
		ssl->sha256.temp1 = ssl->sha256.h + ssl->sha256.ss1 + ssl->sha256.ch +\
							g_sha256_table_k[i] + ssl->sha256.table_w[i];
		ssl->sha256.ss0 = rotate_right_32bit(ssl->sha256.a, 2) ^\
							rotate_right_32bit(ssl->sha256.a, 13) ^\
							rotate_right_32bit(ssl->sha256.a, 22);
		ssl->sha256.maj = (ssl->sha256.a & ssl->sha256.b) ^\
							(ssl->sha256.a & ssl->sha256.c) ^\
							(ssl->sha256.b & ssl->sha256.c);
		ssl->sha256.temp2 = ssl->sha256.ss0 + ssl->sha256.maj;
		ft_sha256_swap_abcdefgh(ssl);
		i++;
	}
	ft_add_sha256_abcdefgh_to_h_values(ssl);
}
