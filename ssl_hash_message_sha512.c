/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_hash_message_sha512.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:15:50 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/12 18:27:36 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	ft_sha512_init(t_ssl *ssl)
{
	ssl->sha512.h0 = 0x6a09e667f3bcc908;
	ssl->sha512.h1 = 0xbb67ae8584caa73b;
	ssl->sha512.h2 = 0x3c6ef372fe94f82b;
	ssl->sha512.h3 = 0xa54ff53a5f1d36f1;
	ssl->sha512.h4 = 0x510e527fade682d1;
	ssl->sha512.h5 = 0x9b05688c2b3e6c1f;
	ssl->sha512.h6 = 0x1f83d9abfb41bd6b;
	ssl->sha512.h7 = 0x5be0cd19137e2179;
}

void	ft_sha512_padding(t_ssl *ssl)
{
	uint64_t	ft_128_bit_representation;
	uint64_t	padding;
	uint64_t	len;
	uint64_t	i;
	uint64_t	swapped_number;

	i = 0;
	len = ft_strlen_uint64(ssl->message_to_digest);
	padding = len;
	ft_128_bit_representation = len * 8;
	padding = calculate_ssl_padding_64bit(padding);
	ssl->sha512.chunk_of_1024bit = (padding + 16) / 128;
	ssl->sha512.padded_message = ft_memalloc(padding + 16);
	ft_strcpy((char *)ssl->sha512.padded_message, ssl->message_to_digest);
	((char *)ssl->sha512.padded_message)[len] = 0x80;
	while (i < (ssl->sha512.chunk_of_1024bit * 16))
	{
		swapped_number = ft_swap_64bit(ssl->sha512.padded_message[i]);
		ssl->sha512.padded_message[i] = swapped_number;
		i++;
	}
	i--;
	ssl->sha512.padded_message[i] = ft_128_bit_representation;
}

void	ft_sha512_transformation(t_ssl *ssl)
{
	uint64_t chunk;

	chunk = 0;
	while (chunk < ssl->sha512.chunk_of_1024bit)
	{
		ft_sha512_process_1024bit_chunk(ssl, chunk);
		ft_sha512_compression(ssl);
		chunk++;
	}
	free(ssl->sha512.padded_message);
}

void	hash_message_sha512(t_ssl *ssl)
{
	ft_bzero(&ssl->sha512, sizeof(ssl->sha512));
	ft_sha512_init(ssl);
	ft_sha512_padding(ssl);
	ft_sha512_transformation(ssl);
	if (ssl->flag.ft_stdin == true || ssl->flag.q == true)
		ft_sha512_print(ssl, '\n');
	else
		ft_sha512_format_print(ssl, "SHA512");
}
