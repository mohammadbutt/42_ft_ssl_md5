/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:18:06 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/12 18:50:17 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void ft_sha384_init(t_ssl *ssl)
{
	ssl->sha512.h0 = 0xcbbb9d5dc1059ed8;
	ssl->sha512.h1 = 0x629a292a367cd507;
	ssl->sha512.h2 = 0x9159015a3070dd17;
	ssl->sha512.h3 = 0x152fecd8f70e5939;
	ssl->sha512.h4 = 0x67332667ffc00b31;
	ssl->sha512.h5 = 0x8eb44a8768581511;
	ssl->sha512.h6 = 0xdb0c2e0d64f98fa7;
	ssl->sha512.h7 = 0x47b5481dbefa4fa4;
}

void	zero_four_variables(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d)
{
	*a = 0;
	*b = 0;
	*c = 0;
	*d = 0;
}

/*
** Adding remaining md5 algos.
** F, G, H, I	✓
** rotate_left	✓
** md5_init		✓
** FF, GG, HH, II
** md5_transform
** md5_update
** md5_final
*/

/*
** Add the below functions in math.c file
*/

uint64_t ft_pow(int base, int exponent)
{
	uint64_t	total;
	int			i;

	total = base;
	i = 1;
	while(i < exponent)
	{
		total = total * base;
		i++;
	}
	return(total);
}

/*
** ft_fabs is used to convert negative floating point values into positive.
**
** Note: Has to be double, data type cannot be float because absolute value will
** be different if the data type is float instead of double.
*/

double ft_fabs(double num)
{
	if(num < 0)
		num = -1 * num;
	return(num);
}
/*
** ft_update_md5_abcd initializes and updates values to be used in the while
** loop.
*/


void zero_three_variables(uint32_t *a, uint32_t *b, uint32_t *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

void ft_sha512_print(t_ssl *ssl, char c)
{
	char *algo;

	algo = ssl->message_digest_algo;
	ft_printf("%016llx%016llx", ssl->sha512.h0, ssl->sha512.h1);
	ft_printf("%016llx%016llx", ssl->sha512.h2, ssl->sha512.h3);
	ft_printf("%016llx%016llx", ssl->sha512.h4, ssl->sha512.h5);
	if (ft_strcmp(algo, "sha384") == 0 || ft_strcmp(algo, "SHA384") == 0)
		ft_printf("%c", c);
	else if (ft_strcmp(algo, "sha512") == 0 || ft_strcmp(algo, "SHA512") == 0)
		ft_printf("%016llx%016llx%c", ssl->sha512.h6, ssl->sha512.h7, c);
}

void	ft_sha512_format_print(t_ssl *ssl, char *algo_name)
{
	if(ssl->flag.r == true && ssl->flag.s == true)
	{
		ft_sha512_print(ssl, ' ');
		ft_printf("\"%s\"\n", ssl->message_to_digest);
	}
	else if(ssl->flag.p == true || ssl->flag.ft_stdin == true)
	{
		ft_sha512_print(ssl, '\n');
		(ssl->flag.ft_stdin == true) && (ft_printf("ft_SSL> "));
		ssl->flag.p = false;
	}
	else if(ssl->flag.r == false && ssl->flag.q == false && ssl->flag.s == true)
	{
		ft_printf("%s (\"%s\") = ", algo_name, ssl->message_to_digest);
		ft_sha512_print(ssl, '\n');
	}
	else if(ssl->flag.s == false)
	{
		ft_printf("%s (%s) = ", algo_name, ssl->file_name);
		ft_sha512_print(ssl, '\n');
	}
}


void hash_message_sha384(t_ssl *ssl)
{
	ft_bzero(&ssl->sha512, sizeof(ssl->sha512));
	ft_sha384_init(ssl);
	ft_sha512_padding(ssl);
	ft_sha512_transformation(ssl);
	if(ssl->flag.ft_stdin == true || ssl->flag.q == true)
		ft_sha512_print(ssl, '\n');
	else
		ft_sha512_format_print(ssl, "SHA384");
}

void ft_initialize_ssl_flag(t_ssl *ssl)
{	
	ft_bzero(&ssl->flag, sizeof(ssl->flag));
	ft_bzero(&ssl->skip, sizeof(ssl->skip));
}

// Cat below---------------------------------------------------------------------
//
//

/*
uint64_t rotate_right_64bit(uint64_t value, uint64_t rotate_n_bits)
{
	uint64_t new_value;

	new_value = ((value >> rotate_n_bits) | (value << (64 - rotate_n_bits)));
	return(new_value);
}

uint64_t	shift_right_64bit(uint64_t value, uint64_t shift_n_bits)
{
	uint64_t new_value;

	new_value = value >> shift_n_bits;
	return(new_value);
}
*/
/*
** Swaps bits of a uint64_t number
*/
/*
uint64_t ft_swap_64bit(uint64_t value)
{
	uint64_t swapped;

	swapped = 0;

	swapped |= (value & 0x00000000000000ff) << 56;
	swapped |= (value & 0x000000000000ff00) << 40;
	swapped |= (value & 0x0000000000ff0000) << 24;
	swapped |= (value & 0x00000000ff000000) << 8;
	swapped |= (value & 0x000000ff00000000) >> 8;
	swapped |= (value & 0x0000ff0000000000) >> 24;
	swapped |= (value & 0x00ff000000000000) >> 40;
	swapped |= (value & 0xff00000000000000) >> 56;
	return(swapped);
}

void ft_bzero_num_array_64bit(uint64_t *num, uint64_t number_of_elements)
{
	uint64_t i;

	i = 0;
	while(i < number_of_elements)
		num[i++] = 0;
}
*/
/*
uint64_t calculate_ssl_padding_64bit(uint64_t padding)
{
	uint64_t ft_128_byte;
	uint64_t ft_112_byte;

	ft_128_byte = (512 * 2)/8;
	ft_112_byte = (448 * 2)/8;
	if(padding % ft_128_byte == ft_112_byte)
		padding =  padding + ft_128_byte;
	else
		while(padding % ft_128_byte != ft_112_byte)
			padding++;
	return(padding);
}
*/
