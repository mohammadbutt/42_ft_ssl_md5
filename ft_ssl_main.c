/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:18:06 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/12 14:49:12 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** Adding sha-256 and sha-512 functions
**
** function rotate_right_32_bit is used for sha-224 and sha-256
**
** function rotate_right_64_bit is used for sha-384 and sha-512
*/

uint32_t rotate_right_32bit(uint32_t value, uint32_t rotate_n_bits)
{
	uint32_t new_value;

	new_value = ((value >> rotate_n_bits) | (value << (32 - rotate_n_bits)));
	return(new_value);
}

uint64_t rotate_right_64bit(uint64_t value, uint64_t rotate_n_bits)
{
	uint64_t new_value;

	new_value = ((value >> rotate_n_bits) | (value << (64 - rotate_n_bits)));
	return(new_value);
}

/*
** How does shifting bits work? Below is a table that shows numerical and binary
** representation:
** Value - binary
**   1   -      1
**   2   -     10
**   4   -    100
**   8   -   1000
**   16  -  10000
**
** So when a value of 16 is bit shifted to the right by 1, it becomes 8.
** And if the value of 16 is bit shifted to the right by 2, it becomes 4.
** Shifting it to the left will move the bit the left and add zero at the tail.
** So when value 16 is bit shifted to left by 1, it becomes 32.
**
** If the seems like values are just getting multiplied and divided by 2, that
** is not what's happening.
** Following are some odd Values with binary representation:
** Value - binary   
**  5    -    101
** When value 5 is bit shifted by 1 to the right it becomes 2:
**  2    -     10
**
**  7    -   1001
** When value 7 is bit shifted by 1 to the right it becomes 3:
** 3     -   100
*/

uint32_t	shift_right_32bit(uint32_t value, uint32_t shift_n_bits)
{
	uint32_t new_value;

	new_value = value >> shift_n_bits;
	return(new_value);
}


uint64_t	shift_right_64bit(uint64_t value, uint64_t shift_n_bits)
{
	uint64_t new_value;

	new_value = value >> shift_n_bits;
	return(new_value);
}

void ft_sha512_init(t_ssl *ssl)
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

/*
** Bitwise guide:
** Bitwise & operator is a binary operator. It takes two numbers.
** & stands for AND operator.
** Result of & AND is 1 when both bits are 1:
** 7 ->   0 1 1 1
** 4 -> & 0 1 0 0
**       --------
** 4 <-   0 1 0 0
**       --------
** 7 & 4 = 4
**
** -----------------------------------------------------------------------------
**
** Bitwise | operator is a binary operator. It takes two numbers.
** | stands for OR operator.
** Result of | OR is 0 when both bits are 0:
** 7 ->   0 1 1 1
** 4 -> | 0 1 0 0
**       --------
** 7 <-   0 1 1 1
**       --------
** 7 | 4 = 7
**
** -----------------------------------------------------------------------------
**
** Bitwise ~ operator is unary operator. It takes one number.
** ~ stands for NOT operator.
** Result of ~ NOT is 0 when bit is 1, and 1 when bit is 0:
** 7 -> ~  0 1 1 1
**        --------
** 8 <-    1 0 0 0
**        --------
** ~ 7  = -8
** How is it -8? because we have to look at the data type 7 is stored in.
** If 7 is stored in a 32 bit int, then:
** 7 -> ~ 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1
**       ----------------------------------------------------------------
** -8 <-  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0
** ~ 7 = -8
** Since the number overflow and goes over the int max value, it becomes -8.
**
** -----------------------------------------------------------------------------
** 
** Bitwise ^ operator is binary operator. It takes two numbers.
** ^ stands for XOR operator.
** Result of ^ XOR is 1 when two bits are different.
** Result of ^ XOR is 0 when two bits are same.
**
** 7 ->    0 1 1 1
** 4 -> ^  0 1 0 0
**         -------
** 3 <-    0 0 1 1
**         -------
** 7 ^ 4 =  3
** Can be used to swap values
*/

void	zero_four_variables(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d)
{
	*a = 0;
	*b = 0;
	*c = 0;
	*d = 0;
}

/*
** Adding md5 core functions
*/
/*
** Swapping bits of value: 123456789
**                                      1        2        3        4
** Original bits:                    00000111 01011011 11001101 00010101
** Step1: bit shift 24 to the left:  00010101 00000000 00000000 00000000
** Step2: bit shift 8  to the left:  00010101 11001101 00000000 00000000
** Step3: bit shift 8  to the right: 00010101 11001101 01011011 00000000
** Step4: bit shift 24 to the right: 00010101 11001101 01011011 00000111
**                                      4        3        2        1
*/
uint32_t ft_swap_32bit(uint32_t value)
{
	uint32_t swapped;

	swapped = 0;
	swapped |= (value & 0x000000FF) << 24;
	swapped |= (value & 0x0000FF00) << 8;
	swapped |= (value & 0x00FF0000) >> 8;
	swapped |= (value & 0xFF000000) >> 24;
    return(swapped);
}

/*
** Swaps bits of a uint64_t number
*/

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

void ft_bzero_num_array_32bit(uint32_t *num, uint32_t number_of_elements)
{
	uint32_t i;

	i = 0;
	while(i < number_of_elements)
		num[i++] = 0;
}

void ft_bzero_num_array_64bit(uint64_t *num, uint64_t number_of_elements)
{
	uint64_t i;

	i = 0;
	while(i < number_of_elements)
		num[i++] = 0;
}


uint32_t calculate_ssl_padding_32bit(uint32_t padding)
{
	uint32_t ft_64_byte;
	uint32_t ft_56_byte;

	ft_64_byte = 512/8;
	ft_56_byte = 448/8;
	if(padding % ft_64_byte == ft_56_byte)
		padding = padding + ft_64_byte;
	else
		while(padding % ft_64_byte != ft_56_byte)
			padding++;
	return(padding);
}

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

void ft_sha512_padding(t_ssl *ssl)
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
	while(i < (ssl->sha512.chunk_of_1024bit * 16))
	{
		swapped_number = ft_swap_64bit(ssl->sha512.padded_message[i]);
		ssl->sha512.padded_message[i] = swapped_number;
		i++;
	}
	i--;
	ssl->sha512.padded_message[i] = ft_128_bit_representation;
}
/*
void test_stored_string(t_ssl *ssl)
{
	size_t i;
	char alpha;

	i = 0;
	alpha = 'A';

	ft_printf(BGREEN"Printing stored string with padding"NC);
	ft_printf("\n");

	while(i < ssl->md5.padded_message_len)
	{
		if(ssl->md5.padded_message[i] == '\0')
			ft_printf(GREEN"%c"NC, alpha++);
		else
			ft_printf("%c", ssl->md5.padded_message[i]);
		i++;
	}
	ft_printf("\nFinished printing stored string with padding\n");
}
*/

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

void ft_update_sha512_abcdefgh(t_ssl *ssl)
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


void ft_add_sha512_abcdefgh_to_h_values(t_ssl *ssl)
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

/*
** 120 bytes is allocated on stack for ssl->sha512.table_w because messages for
** sha512 and sha384 get processed in 1024 chunks.
** 128 bytes * 8 = 1024;
** Allocating space for 128 characters for w is different then going through 80
** rounds to get the new value of w each time.
*/

void ft_sha512_process_1024bit_chunk(t_ssl *ssl, uint64_t chunk)
{
	uint64_t i;
	uint64_t *w;
	uint64_t *padded_message;

	i = 16;
	w = ssl->sha512.table_w;
	padded_message = ssl->sha512.padded_message;
	ft_bzero_num_array_64bit(w, 128);
	ft_memcpy(w, padded_message + (16 * chunk), 128);
	while(i < 80)
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

void ft_sha512_swap_abcdefgh(t_ssl *ssl)
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
void ft_sha512_compression(t_ssl *ssl)
{
	uint32_t i;

	i = 0;
	ft_update_sha512_abcdefgh(ssl);
	while(i < 80)
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
void ft_sha512_transformation(t_ssl *ssl)
{
	uint64_t chunk;

	chunk = 0;
	while(chunk < ssl->sha512.chunk_of_1024bit)
	{
		ft_sha512_process_1024bit_chunk(ssl, chunk);
		ft_sha512_compression(ssl);
		chunk++;
	}
	free(ssl->sha512.padded_message);
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
void hash_message_sha512(t_ssl *ssl)
{
	ft_bzero(&ssl->sha512, sizeof(ssl->sha512));
	ft_sha512_init(ssl);
	ft_sha512_padding(ssl);
	ft_sha512_transformation(ssl);
	if(ssl->flag.ft_stdin == true || ssl->flag.q == true)
		ft_sha512_print(ssl, '\n');
	else
		ft_sha512_format_print(ssl, "SHA512");
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


//------------------------------------------------- Cat below

void hash_message_sha224(t_ssl *ssl)
{
	ft_bzero(&ssl->sha256, sizeof(ssl->sha256));
	ft_sha224_init(ssl);
	ft_sha256_padding(ssl);
	ft_sha256_transformation(ssl);
	if(ssl->flag.ft_stdin == true || ssl->flag.q == true)
		ft_sha256_print(ssl, '\n');
	else
		ft_sha256_format_print(ssl, "SHA224");
}


void ft_sha224_init(t_ssl *ssl)
{
	ssl->sha256.h0 = 0xc1059ed8;
	ssl->sha256.h1 = 0x367cd507;
	ssl->sha256.h2 = 0x3070dd17;
	ssl->sha256.h3 = 0xf70e5939;
	ssl->sha256.h4 = 0xffc00b31;
	ssl->sha256.h5 = 0x68581511;
	ssl->sha256.h6 = 0x64f98fa7;
	ssl->sha256.h7 = 0xbefa4fa4;
}

//--------------------------------------------------- Cat below

void ft_update_sha256_abcdefgh(t_ssl *ssl)
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

void ft_add_sha256_abcdefgh_to_h_values(t_ssl *ssl)
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


void ft_sha256_swap_abcdefgh(t_ssl *ssl)
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


void ft_sha256_process_512bit_chunk(t_ssl *ssl, uint32_t chunk)
{
	uint32_t i;
	uint32_t *w;
	uint32_t *padded_message;

	i = 16;
	w = ssl->sha256.table_w;
	padded_message = ssl->sha256.padded_message;
	ft_bzero_num_array_32bit(w, 64);
	ft_memcpy(w, padded_message + (16 * chunk), 64);
	while(i < 64)
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



void ft_sha256_compression(t_ssl *ssl)
{
	uint32_t i;

	i = 0;
	ft_update_sha256_abcdefgh(ssl);
	while(i < 64)
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

// ------------------------------------------------------------ Cat below

void ft_sha256_print(t_ssl *ssl, char c)
{
	char *algo;

	algo = ssl->message_digest_algo;
	ft_printf("%08x%08x%08x", ssl->sha256.h0, ssl->sha256.h1, ssl->sha256.h2);
	ft_printf("%08x%08x%08x", ssl->sha256.h3, ssl->sha256.h4, ssl->sha256.h5);
	ft_printf("%08x", ssl->sha256.h6);
	if (ft_strcmp(algo, "sha224") == 0 || ft_strcmp(algo, "SHA224") == 0)
		ft_printf("%c", c);
	else if(ft_strcmp(algo, "sha256") == 0 || ft_strcmp(algo, "SHA256") == 0)
		ft_printf("%08x%c", ssl->sha256.h7, c);
}


void	ft_sha256_format_print(t_ssl *ssl, char *algo_name)
{
	if(ssl->flag.r == true && ssl->flag.s == true)
	{
		ft_sha256_print(ssl, ' ');
		ft_printf("\"%s\"\n", ssl->message_to_digest);
	}
	else if(ssl->flag.p == true || ssl->flag.ft_stdin == true)
	{
		ft_sha256_print(ssl, '\n');
		(ssl->flag.ft_stdin == true) && (ft_printf("ft_SSL> "));
		ssl->flag.p = false;
	}
	else if(ssl->flag.r == false && ssl->flag.q == false && ssl->flag.s == true)
	{
		ft_printf("%s (\"%s\") = ", algo_name, ssl->message_to_digest);
		ft_sha256_print(ssl, '\n');
	}
	else if(ssl->flag.s == false)
	{
		ft_printf("%s (%s) = ", algo_name, ssl->file_name);
		ft_sha256_print(ssl, '\n');
	}
}

//------------------------------------------------------- Cat below

/*
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

void ft_sha256_padding(t_ssl *ssl)
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
	while(i < (ssl->sha256.chunk_of_512bit * 16))
	{
		swapped_number = ft_swap_32bit(ssl->sha256.padded_message[i]);
		ssl->sha256.padded_message[i] = swapped_number;
		i++;
	}
	i--;
	ssl->sha256.padded_message[i] = ft_64_bit_representation;
}


void ft_sha256_transformation(t_ssl *ssl)
{
	uint32_t	chunk;

	chunk = 0;
	while(chunk < ssl->sha256.chunk_of_512bit)
	{
		ft_sha256_process_512bit_chunk(ssl, chunk);
		ft_sha256_compression(ssl);
		chunk++;
	}
	free(ssl->sha256.padded_message);
}

void hash_message_sha256(t_ssl *ssl)
{
	ft_bzero(&ssl->sha256, sizeof(ssl->sha256));
	ft_sha256_init(ssl);	
	ft_sha256_padding(ssl);	
	ft_sha256_transformation(ssl);
	if(ssl->flag.ft_stdin == true || ssl->flag.q == true)
		ft_sha256_print(ssl, '\n');
	else
		ft_sha256_format_print(ssl, "SHA256");
}
*/
