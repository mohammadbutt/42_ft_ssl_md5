/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_hash_message_sha256.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:45:35 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/12 14:52:24 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	ft_sha256_init(t_ssl *ssl)
{
	ssl->sha256.h0 = 0x6a09e667;
	ssl->sha256.h1 = 0xbb67ae85;
	ssl->sha256.h2 = 0x3c6ef372;
	ssl->sha256.h3 = 0xa54ff53a;
	ssl->sha256.h4 = 0x510e527f;
	ssl->sha256.h5 = 0x9b05688c;
	ssl->sha256.h6 = 0x1f83d9ab;
	ssl->sha256.h7 = 0x5be0cd19;
}

void	ft_sha256_padding(t_ssl *ssl)
{
	uint32_t	ft_64_bit_representation;
	uint32_t	padding;
	uint32_t	len;
	uint32_t	i;
	uint32_t	swapped_number;

	i = 0;
	len = ft_strlen_uint32(ssl->message_to_digest);
	padding = len;
	ft_64_bit_representation = len * 8;
	padding = calculate_ssl_padding_32bit(padding);
	ssl->sha256.chunk_of_512bit = (padding + 8) / 64;
	ssl->sha256.padded_message = ft_memalloc(padding + 8);
	ft_strcpy((char *)ssl->sha256.padded_message, ssl->message_to_digest);
	((char *)ssl->sha256.padded_message)[len] = 0x80;
	while (i < (ssl->sha256.chunk_of_512bit * 16))
	{
		swapped_number = ft_swap_32bit(ssl->sha256.padded_message[i]);
		ssl->sha256.padded_message[i] = swapped_number;
		i++;
	}
	i--;
	ssl->sha256.padded_message[i] = ft_64_bit_representation;
}

void	ft_sha256_transformation(t_ssl *ssl)
{
	uint32_t	chunk;

	chunk = 0;
	while (chunk < ssl->sha256.chunk_of_512bit)
	{
		ft_sha256_process_512bit_chunk(ssl, chunk);
		ft_sha256_compression(ssl);
		chunk++;
	}
	free(ssl->sha256.padded_message);
}

void	hash_message_sha256(t_ssl *ssl)
{
	ft_bzero(&ssl->sha256, sizeof(ssl->sha256));
	ft_sha256_init(ssl);
	ft_sha256_padding(ssl);
	ft_sha256_transformation(ssl);
	if (ssl->flag.ft_stdin == true || ssl->flag.q == true)
		ft_sha256_print(ssl, '\n');
	else
		ft_sha256_format_print(ssl, "SHA256");
}
