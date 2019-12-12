/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_hash_message_md5.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 13:25:04 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/12 13:53:45 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** Values to initialize md5.a0, b0, c0, d0.
** Values takes from wikipedia.
*/

void	ft_md5_init(t_ssl *ssl)
{
	ssl->md5.a0 = 0x67452301;
	ssl->md5.b0 = 0xefcdab89;
	ssl->md5.c0 = 0x98badcfe;
	ssl->md5.d0 = 0x10325476;
}

/*
** why do we malloc padding + 8 ?
** Because in md5 padded string will be 64 bits less than 512, and the final
** padded string will be a multiple of 512 bits or 64 bytes which is why 8 bits
** are added.
** Below are some examples in Bits and bytes:
** padding = 448 bits or 56 bytes
** Bits: malloc (padding + 64 bits) => 448 + 64 => 512bit is a multiple of 512
** Byte: malloc (padding + 8 byte)  => 56 + 8 =>   64byte is a multiple of 512
**
** padding = 960
** malloc (padding + 64) => 960 + 64 => 1024 is a multiple of 512
**
** padding = 1472
** malloc (padding + 64) => 1472 + 64 = 1536 is a multiple of 512
**
** A lot of my caluclations are in bytes, instead of bits.
** 1 byte = 8 bits
*/

void	ft_md5_padding(t_ssl *ssl)
{
	uint32_t	ft_64_bit_representation;
	uint32_t	padding;
	uint32_t	len;

	len = ft_strlen_uint32(ssl->message_to_digest);
	padding = len;
	ft_64_bit_representation = len * 8;
	padding = calculate_ssl_padding_32bit(padding);
	ssl->md5.padded_message = ft_memalloc(padding + 8);
	ft_strcpy(ssl->md5.padded_message, ssl->message_to_digest);
	ssl->md5.padded_message[len] = 0x80;
	ssl->md5.padded_message_len = padding;
	*(uint32_t*)(ssl->md5.padded_message + padding) = ft_64_bit_representation;
}

/*
** break chunk into sixteen 32-bit words
** chunk_of_64_byte = 512 bits
*/

void	ft_md5_transformation(t_ssl *ssl)
{
	uint32_t	*str;
	uint32_t	chunk_of_64_byte;
	uint32_t	i;
	uint32_t	f;

	zero_three_variables(&chunk_of_64_byte, &i, &f);
	compute_md5_table_g_k_s(ssl);
	while (chunk_of_64_byte < ssl->md5.padded_message_len)
	{
		ft_update_md5_abcd(ssl);
		str = (uint32_t *)(ssl->md5.padded_message + chunk_of_64_byte);
		i = 0;
		while (i < FT_64_BYTE)
		{
			f = md5_function_fghi(i, ssl->md5.b, ssl->md5.c, ssl->md5.d);
			f = f + ssl->md5.a + ssl->md5.table_k[i] + str[ssl->md5.table_g[i]];
			swap_md5_adc_with_dcb(ssl);
			ssl->md5.b = ssl->md5.b + rotate_left_32bit(f, ssl->md5.table_s[i]);
			i++;
		}
		ft_add_md5_abcd_to_a0b0c0d0(ssl);
		chunk_of_64_byte = chunk_of_64_byte + FT_64_BYTE;
	}
	free(ssl->md5.padded_message);
}

void	ft_md5_format_print(t_ssl *ssl)
{
	if (ssl->flag.r == true && ssl->flag.s == true)
	{
		ft_md5_print(ssl, ' ');
		ft_printf("\"%s\"\n", ssl->message_to_digest);
	}
	else if (ssl->flag.p == true || ssl->flag.ft_stdin == true)
	{
		ft_md5_print(ssl, '\n');
		(ssl->flag.ft_stdin == true) && (ft_printf("ft_SSL> "));
		ssl->flag.p = false;
	}
	else if (ssl->flag.r == false && ssl->flag.s == true)
	{
		ft_printf("MD5 (\"%s\") = ", ssl->message_to_digest);
		ft_md5_print(ssl, '\n');
	}
	else if (ssl->flag.s == false)
	{
		ft_printf("MD5 (%s) = ", ssl->file_name);
		ft_md5_print(ssl, '\n');
	}
}

/*
** ft_bzero(&ssl->md5, sizeof(t_ssl_md5)); is the same as below:
** ft_bzero(&ssl->md5, sizeof(ssl->md5));
*/

void	hash_message_md5(t_ssl *ssl)
{
	ft_bzero(&ssl->md5, sizeof(ssl->md5));
	ft_md5_init(ssl);
	ft_md5_padding(ssl);
	ft_md5_transformation(ssl);
	swap_bits_to_fix_endian(ssl);
	if (ssl->flag.ft_stdin == true || ssl->flag.q == true)
		ft_md5_print(ssl, '\n');
	else
		ft_md5_format_print(ssl);
}
