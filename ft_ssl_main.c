/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:18:06 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/07 21:52:45 by mbutt            ###   ########.fr       */
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


/*
** Adding md5 core functions
*/

uint32_t md5_function_f(uint32_t b, uint32_t c, uint32_t d)
{
	uint32_t f;

//	f = (((b) & (c)) | ((~b) & (d)));
	f = (b & c) | ((~b) & d);
	return(f);
}

uint32_t md5_function_g(uint32_t b, uint32_t c, uint32_t d)
{
	uint32_t g;

//	g = (((b) & (d)) | ((c) & (~d)));
	g = (d & b) | ((~d) & c);
	return(g);
}

uint32_t md5_function_h(uint32_t b, uint32_t c, uint32_t d)
{
	uint32_t h;
	
//	h = ((b) ^ (c) ^ (d));
	h = (b ^ c ^ d);
	return(h);
}

uint32_t md5_function_i(uint32_t b, uint32_t c, uint32_t d)
{
	uint32_t i;

//	i = ((c) ^ ((b) | (~d)));
	i = c ^ (b | (~d));
	return(i);
}

uint32_t md5_function_fghi(uint32_t i, uint32_t b, uint32_t c, uint32_t d)
{
	uint32_t f;
	
	f = 0;
	if(i >= 0 && i <= 15)
		f = md5_function_f(b, c, d);
	else if(i >= 16 && i <= 31)
		f = md5_function_g(b, c, d);
	else if(i >= 32 && i <= 47)
		f = md5_function_h(b, c, d);
	else if(i >= 48 && i <= 63)
		f = md5_function_i(b, c, d);
	return(f);
}

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

//void compute_md5_table_x(uint32_t *num)
void compute_md5_table_g(uint32_t *num)
{
	uint32_t i;
	uint32_t j;

	i = 0;
	j = 0;
	while(j <= 15)
		num[i++] = j++;
	while(j <= 31)
		num[i++] = ((5 * j++) + 1) % 16;
	while(j <= 47)
		num[i++] = ((3 * j++) + 5) % 16;
	while(j <= 63)
		num[i++] = (7 * j++) % 16;
}

/*
** rotate_left rotates x by n bits for md5
*/
uint32_t rotate_left_32bit(uint32_t value, uint32_t rotate_n_bits)
{
	uint32_t new_value;

//	rotated_number = (((f) << (n_bits)) | ((f) >> (32 - (n_bits))));
	new_value = ((value << rotate_n_bits) | (value >> (32 - rotate_n_bits)));
	return(new_value);
}

/*
uint32_t ft_swap_bits_1(uint32_t x)
{
      uint32_t y;

	  y = (x >> 24) & 0xff;
      y |= ((x >> 16) & 0xff) << 8;
      y |= ((x >> 8) & 0xff) << 16;
      y |= (x & 0xff) << 24;
	  return(y);
}
*/

void	set_md5_to_zero(t_ssl *ssl)
{
	ssl->md5.padded_message_len = 0;
	ssl->md5.a0 = 0;
	ssl->md5.b0 = 0;
	ssl->md5.c0 = 0;
	ssl->md5.d0 = 0;
	ssl->md5.a = 0;
	ssl->md5.b = 0;
	ssl->md5.c = 0;
	ssl->md5.d = 0;
}

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
void ft_md5_init(t_ssl *ssl)
{
	int i;

	i = 0;
	ssl->context.state[i++] = 0x67452301;
	ssl->context.state[i++] = 0xefcdab89;
	ssl->context.state[i++] = 0x98badcfe;
	ssl->context.state[i] = 0x10325476;
	ssl->context.count[0] = 0;
	ssl->context.count[1] = 0;
//	ft_bzero(ssl->context.count, sizeof(ssl->context.count));
}
*/
void ft_md5_init(t_ssl *ssl)
{
/*
	ssl->state.a0 = 0x67452301;
	ssl->state.b0 = 0xefcdab89;
	ssl->state.c0 = 0x98badcfe;
	ssl->state.d0 = 0x10325476;
*/

	ssl->md5.a0 = 0x67452301;
	ssl->md5.b0 = 0xefcdab89;
	ssl->md5.c0 = 0x98badcfe;
	ssl->md5.d0 = 0x10325476;
}

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


//void compute_md5_table_s_0_to_31(unsigned int *num)
void compute_md5_table_s_0_to_31(uint32_t *num)
{
	int i;

	i = 0;
	while(i >= 0 && i <= 15)
	{
		num[i++] = 7;
		num[i++] = 12;
		num[i++] = 17;
		num[i++] = 22;
	}
	while(i >= 16 && i <= 31)
	{
		num[i++] = 5;
		num[i++] = 9;
		num[i++] = 14;
		num[i++] = 20;
	}
}

//void compute_md5_table_s_32_to_63(unsigned int *num)
void compute_md5_table_s_32_to_63(uint32_t *num)
{
	int i;

	i = 32;
	while (i >= 32 && i <= 47)
	{
		num[i++] = 4;
		num[i++] = 11;
		num[i++] = 16;
		num[i++] = 23;
	}
	while (i >= 48 && i <= 63)
	{
		num[i++] = 6;
		num[i++] = 10;
		num[i++] = 15;
		num[i++] = 21;
	}
}
/*
** s specifies the pre round shift amount
** compute_table_functions:
** compute_md5_table_s ✓
** compute_md5_table_k ✓
** compute_md5_table_m, g_md5_table_m -> in header ✓ 
** compute_md5_table_padding ✓
*/
//void compute_md5_table_s(unsigned int *num)
void compute_md5_table_s(uint32_t *num)
{
//	ft_printf(BGREEN"%lu"NC,(sizeof(num) * sizeof(num)));
//	ft_printf("\n");
//	ft_bzero(num, (sizeof(num) * sizeof(num)));
	ft_bzero(num, (64 * 4));
	compute_md5_table_s_0_to_31(num);
	compute_md5_table_s_32_to_63(num);
}

//void compute_md5_table_k(unsigned int *num)
void compute_md5_table_k(uint32_t *num)
{
	uint32_t i;
	int base;
	int exponent;

	i = 0;
	base = 2;
	exponent = 32;
	ft_bzero(num, (64 * 4));
	while(i < 64)
	{
		num[i] = (uint32_t)(ft_pow(base, exponent) * ft_fabs(sin(i + 1)));
		i++;
	}		
}

void compute_md5_table_g_k_s(t_ssl *ssl)
{
	compute_md5_table_g(ssl->md5.table_g);
	compute_md5_table_k(ssl->md5.table_k);
	compute_md5_table_s(ssl->md5.table_s);
}

/*
void compute_md5_table_padding(unsigned char *num)
{
//	ft_printf(BBLUE"%lu"NC, (sizeof(num)));
//	ft_printf("\n");
	ft_bzero(num, 64);
	num[0] = 0x80;
}
*/

//void	*ft_memalloc(size_t size);

uint32_t calculate_ssl_padding_32bit(uint32_t padding)
{
/*
	if(padding % (512/8) == (448/8))
		padding = padding + 64;
	else
		while(padding % (512/8) != (448/8))
			padding++;
	return(padding);
*/
/*
	if(padding % FT_512_BIT == FT_448_BIT)
		padding = padding + FT_512_BIT;
	else
		while(padding % FT_512_BIT != FT_448_BIT)
			padding++;
	return(padding);
*/
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

/*
** why do we malloc padding + 8 ?
** Because in md5 padded string will be 64 bits less than 512, and the final
** padded string will be a multiple of 512 bits  or 64 bytes which is why 8 bits
** are added.
** Below are some examples in Bits and bytes:
** padding = 448 bits or 56 bytes
** Bits: malloc (padding + 64 bits) => 448 + 64 => 512bit is a multiple of 512
** Byte: malloc (padding + 8 byte)  => 56 + 8 =>   64byte is a multiple of 512

** padding = 960
** malloc (padding + 64) => 960 + 64 => 1024 is a multiple of 512
**
** padding = 1472
** malloc (padding + 64) => 1472 + 64 = 1536 is a multiple of 512
**
** A lot of my caluclations are in bytes, instead of bits.
** 1 byte = 8 bits
*/

void ft_md5_padding(t_ssl *ssl)
{
	uint32_t	ft_64_bit_representation;
	uint32_t	padding;
	uint32_t	len;
//	uint32_t	i;

//	i = 0;
	len = ft_strlen_uint32(ssl->message_to_digest);
	padding = len;
	ft_64_bit_representation = len * 8;
//	if(padding % (512/8) == (448/8))
//		padding = padding + 64;
//	else
//		while(padding % (512/8) != (448/8))
//			padding++;
	padding = calculate_ssl_padding_32bit(padding);
	ft_printf("padding:|%u|\n", padding);

//	ssl->md5.padded_message = ft_memalloc(padding + 8);

	ssl->md5.padded_message = ft_memalloc(padding + 8);
//	ssl->md5.padded_message = ft_memalloc(padding + 64);
	ft_strcpy(ssl->md5.padded_message, ssl->message_to_digest);
//	i = len;
//	ssl->md5.padded_message[i++] = 0x80;
	ssl->md5.padded_message[len] = 0x80;

//	while(i < padding)                    // Can be removed since we used memalloc
//		ssl->md5.padded_message[i++] = 0; // Cane be remove since we use memalloc
//	i = padding;                          // Can be used instead;

	ssl->md5.padded_message_len = padding;
//	*(uint32_t*)(ssl->md5.padded_message + i) = ft_64_bit_representation;

	*(uint32_t*)(ssl->md5.padded_message + padding) = ft_64_bit_representation;
//	ssl->md5.padded_message[(int)i] = ft_64_bit_representation;
}


void ft_sha256_padding(t_ssl *ssl)
{
	uint32_t	ft_64_bit_representation;
	uint32_t	padding;
	uint32_t	len;
	uint32_t	i;
	uint32_t	swapped_number;
//	uint32_t	number_of_512bit_chunk;

	i = 0;
	len = ft_strlen_uint32(ssl->message_to_digest);
	padding = len;
	ft_64_bit_representation = len * 8;
	padding = calculate_ssl_padding_32bit(padding);
//	ssl->sha256.number_of_512bit_chunk = (padding + (64/8)) / (512/8);

//	ssl->sha256.number_of_512bit_chunk = (padding + 8) / 64;

	ssl->sha256.chunk_of_512bit = (padding + 8) / 64;
//	ssl->sha256.number_of_512bit_chunk = (padding + FT_64_BIT) / (FT_512_BIT);
	ssl->sha256.padded_message = ft_memalloc(padding + 8);
	ft_strcpy((char *)ssl->sha256.padded_message, ssl->message_to_digest);
	((char *)ssl->sha256.padded_message)[len] = 0x80;
//	while(i < (ssl->sha256.number_of_512bit_chunk * 16))	
	while(i < (ssl->sha256.chunk_of_512bit * 16))
	{
		swapped_number = ft_swap_32bit((uint32_t)ssl->sha256.padded_message[i]);
		ssl->sha256.padded_message[i++] = swapped_number;
	}
	i--;
	*(uint32_t *)(ssl->sha256.padded_message + i) = ft_64_bit_representation;
}


/*
void ft_sha256_padding(t_ssl *ssl)
{
	uint32_t	ft_64_bit_representation;
	uint32_t	padding;
	uint32_t	len;
	uint32_t	i;
	uint32_t	swapped_message;

	i = 0;
	len = ft_strlen_uint32(ssl->message_to_digest);
	padding = len;
	ft_64_bit_representation = len * 8;
	ft_printf("Comes here\n");
	padding = calculate_ssl_padding_32bit(padding);
	ft_printf("Comes here\n");
	ssl->sha256.padded_message = ft_memalloc(padding + 64);
	ft_printf(BGREEN"Malloc succesful\n"NC);
//	ft_strcpy(ssl->sha256.padded_message, ssl->message_to_digest);
	i = len;
	ssl->sha256.padded_message[i++] = 0x80;
	while(i < padding)
		ssl->sha256.padded_message[i++] = 0;
	i = 0;
	ft_printf("%s\n", ssl->sha256.padded_message);
	while(i < padding)
	{
		swapped_message = ft_swap_32bit((uint32_t)ssl->sha256.padded_message[i]);
		ssl->sha256.padded_message[i] = swapped_message;
		ft_printf("|%02u|%c|\n", i, ssl->sha256.padded_message[i]);
		i++;
	}
	ssl->sha256.padded_message_len = padding;
	*(uint32_t *)(ssl->sha256.padded_message + i) = ft_64_bit_representation;

//	test_ft_sha256_padding(ssl);
}
*/

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

/*
//void ft_md5_padding(t_ssl *ssl, char *msg, size_t len)
void ft_md5_padding(t_ssl *ssl, uint8_t *msg, size_t len)
{
	size_t		i;
	uint32_t	ft_64_bit_representation;

	ssl->md5.padded_message_len = len;
	ft_64_bit_representation = len * 8;
	if (ssl->md5.padded_message_len % (512/8) == (448/8))
		ssl->md5.padded_message_len = ssl->md5.padded_message_len + 64;
	else
		while(ssl->md5.padded_message_len % (512/8) != (448/8))
			ssl->md5.padded_message_len++;	
	ssl->md5.padded_message = malloc(sizeof(char) * (ssl->md5.padded_message_len + (ssl->md5.padded_message_len/8)));
	if(ssl->md5.padded_message == NULL)
		return;
//	ft_bzero(ssl->md5.padded_message, ssl->md5.padded_message_len);
//	ft_strcpy_const((char *)ssl->md5.padded_message, (const char *)msg);
	ft_strcpy((char *)ssl->md5.padded_message, (char *)msg);
	i = len;
	ssl->md5.padded_message[i++] = 0x80;
	while(i < ssl->md5.padded_message_len)
		ssl->md5.padded_message[i++] = '-';
	*(uint32_t*)(ssl->md5.padded_message + i) = ft_64_bit_representation;

//	test_stored_string(ssl);


	ft_printf("ft_64_bit_representation|%u|\n", ft_64_bit_representation);
	ft_printf("len        |%u|\n", len);
	ft_printf("i          |%u|\n", i);
	ft_printf("message_len|%u|\n", ssl->md5.padded_message_len);
	ft_printf("message    |%s|\n", ssl->md5.padded_message);
	ft_printf("total_u    |%u|\n", ssl->md5.padded_message);

//	int j = 0;
//	while(j < 100)
//	{
//		if(j + 1 == (int)ssl->md5.padded_message_len)
//		{
//			ft_printf("char[%02d]    |%c|%u|\n", j, ssl->md5.padded_message[j], ssl->md5.padded_message[j]);
//			ft_printf(BRED"char[%02d]    |%c|%u|"NC, j, '*', ssl->md5.padded_message[j]);
//			write(1, "\n", 1);
//		}
//		else
//		ft_printf("char[%02d]    |%c|%u|\n", j, ssl->md5.padded_message[j], ssl->md5.padded_message[j]);
//		j++;
//	}

	exit(EXIT_SUCCESS);
}
*/

//void compute_md5_table_padding()

/*
** print_error_messages takes a 2d array and if the file descriptor is -1, then
** the error message is printed.
** File desciptor will be -1 under 1 of 2 conditions:
** 1. A file path is an invalid file path. "No such file or directory"
** 2. A file has permission denied access. "Permission denied"
*/

void error_invalid_file_permission(int fd, char *argv)
{
	ft_printf("ft_ssl: %s: %s\n", argv, strerror(errno));
//	fd = fd * 1;
	close(fd);
//	exit(EXIT_SUCCESS);
}


//void test_md5_table_k(void)
void test_md5_table_k(t_ssl *ssl)
{
//	uint32_t num[64];
	uint32_t i;

	i = 0;
//	ft_bzero(num, sizeof(num));
//	compute_md5_table_k(num);
/*
	while(i < 64)
	{
		if(((i) % 4) == 0)
			printf("{ ");
		printf("%#x, ", ssl->md5.table_k[i]);
		if(((i + 1) % 4) == 0)
			printf("}\n\n");
		i++;
	}
*/
	while(i < 64)
	{
		ft_printf("|%u|%u|\n", i, ssl->md5.table_k[i]);
		i++;
	}
}

//void test_md5_table_s(void)
void	test_md5_table_s(t_ssl *ssl)
{
//	uint32_t num[64];
	uint32_t i;

	i = 0;
//	compute_md5_table_s(num);
	while(i < 64)
	{
		if(i == 0 || i == 16 || i == 32 || i == 48)
			printf("{ ");
		printf("%u, ", ssl->md5.table_s[i]);
		if(i == 15 || i == 31 || i == 47 || i == 63)
			printf("}\n\n");
		i++;
	}

}

void test_md5_table_g(t_ssl *ssl)
{
//	uint32_t num[64];
	uint32_t i;

	i = 0;
//	compute_md5_table_x(num);
//	compute_md5_table_g(num);

	while(i < 64)
	{
		printf("|%d|\n", ssl->md5.table_g[i]);
		i++;
	}
	printf("\nDone printing table_x\n\n");

}


/*
** ft_update_md5_abcd initializes and updates values to be used in the while
** loop.
*/
/*
void ft_md5_update_context_abcd(t_ssl *ssl)
{

	ssl->context.a = ssl->context.state[0];
	ssl->context.b = ssl->context.state[1];
	ssl->context.c = ssl->context.state[2];
	ssl->context.d = ssl->context.state[3];

}
*/

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

void ft_update_md5_abcd(t_ssl *ssl)
{
/*
	ssl->state.a = ssl->state.a0;
	ssl->state.b = ssl->state.b0;
	ssl->state.c = ssl->state.c0;
	ssl->state.d = ssl->state.d0;
*/

	ssl->md5.a = ssl->md5.a0;
	ssl->md5.b = ssl->md5.b0;
	ssl->md5.c = ssl->md5.c0;
	ssl->md5.d = ssl->md5.d0;
}

/*
** Adds the newly retrieved values of a, b, c, d to ssl->md5.a0, ssl->md5.b0,
** ssl->md5.c0, and ssl->md5.d0
*/

void ft_add_md5_abcd_to_a0b0c0d0(t_ssl *ssl)
{
/*
	ssl->state.a0 = ssl->state.a0 + ssl->state.a;
	ssl->state.b0 = ssl->state.b0 + ssl->state.b;
	ssl->state.c0 = ssl->state.c0 + ssl->state.c;
	ssl->state.d0 = ssl->state.d0 + ssl->state.d;
*/

	ssl->md5.a0 = ssl->md5.a0 + ssl->md5.a;
	ssl->md5.b0 = ssl->md5.b0 + ssl->md5.b;
	ssl->md5.c0 = ssl->md5.c0 + ssl->md5.c;
	ssl->md5.d0 = ssl->md5.d0 + ssl->md5.d;
}


void set_variables_to_zero(uint32_t *a, uint32_t *b, uint32_t *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

void swap_bits_to_fix_endian(t_ssl *ssl)
{
	ssl->md5.a0 = ft_swap_32bit(ssl->md5.a0);
	ssl->md5.b0 = ft_swap_32bit(ssl->md5.b0);
	ssl->md5.c0 = ft_swap_32bit(ssl->md5.c0);
	ssl->md5.d0 = ft_swap_32bit(ssl->md5.d0);
}

void swap_md5_adc_with_dcb(t_ssl *ssl)
{
	ssl->md5.a = ssl->md5.d;
	ssl->md5.d = ssl->md5.c;
	ssl->md5.c = ssl->md5.b;
}

/*
** break chunk into sixteen 32-bit words
** chunk_of_64_byte = 512 bits
*/

void ft_md5_transformation(t_ssl *ssl)
{
	uint32_t *str;
	uint32_t chunk_of_64_byte;
	uint32_t i;
	uint32_t f;

	set_variables_to_zero(&chunk_of_64_byte, &i, &f);
	compute_md5_table_g_k_s(ssl);
	while(chunk_of_64_byte < ssl->md5.padded_message_len)
	{
		ft_update_md5_abcd(ssl);
		str = (uint32_t *)(ssl->md5.padded_message + chunk_of_64_byte);
		i = 0;
		while(i < FT_64_BYTE)
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
/*
uint32_t sha256_rotate_shift_w_for_s0(t_ssl *ssl, uint32_t i)
{
	uint32_t s0;
	uint32_t value1;
	uint32_t value2;
	uint32_t value3;

	value1 = rotate_right_32bit(w[i - 15], 7);
	value2 = rotate_right_32bit(w[i - 15], 18);
	value3 = shift_right_32bit(w[i - 15], 3);
	s0 = valu1 ^ value2 ^ value3;
	return(s0);
}

uint32_t sha256_rotate_shift_w_for_s1(t_ssl *ssl, uint32_t i)
{
	uint32_t s1;
	uint32_t value1;
	uint32_t value2;
	uint32_t value3;

	value1 = rotate_right_32bit(w[i - 2], 17);
	value2 = rotate_right_32bit(w[i - 2], 19);
	value3 = shift_right_32bit(w[i - 2], 10);
	return(s1);
}
*/
void ft_sha256_process_512bit_chunk(t_ssl *ssl)
{
	uint32_t i;
	uint32_t *w;
	uint32_t *padded_message;
	uint32_t chunk_of_512bit;

	i = 0;
	w = ssl->sha256.table_w;
	padded_message = ssl->sha256.padded_message;
	chunk_of_512bit = ssl->sha256.chunk_of_512bit;
	ft_bzero_num_array_32bit(w, 64);
	ft_memcpy(w, padded_message + (16 * chunk_of_512bit), 64);
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
						 ((~ssl->sha256.e) & (ssl->sha256.g));
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
/*
void calculate_sha256_s0_s1_w(t_ssl *ssl)
{
	uint32_t i;

	i = 16;
	while()
}
*/
void ft_sha256_transformation(t_ssl *ssl)
{
	uint32_t	chunk;
//	uint32_t	i;

	chunk = 0;
//	i = 16;
//	while(chunk < ssl->sha256.number_of_512bit_chunk)
	while(chunk < ssl->sha256.chunk_of_512bit)
	{
		ft_sha256_process_512bit_chunk(ssl);
//		ft_update_sha256_abcdefgh(ssl);
		ft_sha256_compression(ssl);
//		ft_add_sha256_abcdefgh_to_h_values(ssl);
		chunk++;
	}
}


void ft_md5_print(t_ssl *ssl, char character)
{
//	uint32_t	a0;
//	uint32_t	b0;
//	uint32_t	c0;
//	uint32_t	d0;

//	a0 = ssl->md5.a0;
//	b0 = ssl->md5.b0;
//	c0 = ssl->md5.c0;
//	d0 = ssl->md5.d0;
//	ft_printf("%x%x%x%x%c", a0, b0, c0, d0, character);
	ft_printf("%x%x%x", ssl->md5.a0, ssl->md5.b0, ssl->md5.c0);
	ft_printf("%x%c", ssl->md5.d0, character);
}

void ft_md5_format_print(t_ssl *ssl)
{
	if(ssl->flag.q == true  && ssl->flag.s == true)
		ft_md5_print(ssl, '\n');
	else if(ssl->flag.r == true && ssl->flag.s == true)
	{
		ft_md5_print(ssl, ' ');
		ft_printf("\"%s\"\n", ssl->message_to_digest);
	}
	else if(ssl->flag.p == true)
	{
//		ft_printf("MD5 (\"%s\") = ", ssl->message_to_digest);
		ft_md5_print(ssl, '\n');
		ssl->flag.p = false;
	}
	else if(ssl->flag.r == false && ssl->flag.q == false && ssl->flag.s == true)
	{
		ft_printf("MD5 (\"%s\") = ", ssl->message_to_digest);
		ft_md5_print(ssl, '\n');
	}
	else if(ssl->flag.s == false)
	{
		ft_printf("MD5 (%s) = ", ssl->file_name);
		ft_md5_print(ssl, '\n');
	}

//	else if(ssl->flag.q == false && ssl->flag.r == false && ssl->flag.p == true)
//	{
//		ft_print
//	}

}

/*
** ft_bzero(&ssl->md5, sizeof(t_ssl_md5)); is the same as below:
** ft_bzero(&ssl->md5, sizeof(ssl->md5));
*/

void hash_message_md5(t_ssl *ssl)
{
	ft_bzero(&ssl->md5, sizeof(ssl->md5));
	ft_md5_init(ssl);
	ft_md5_padding(ssl);
	ft_md5_transformation(ssl);
	swap_bits_to_fix_endian(ssl);
	ft_md5_format_print(ssl);
}

void ft_sha256_print(t_ssl *ssl, char c)
{
	ft_printf("%x%x%x", ssl->sha256.h0, ssl->sha256.h1, ssl->sha256.h2);
	ft_printf("%x%x%x", ssl->sha256.h3, ssl->sha256.h4, ssl->sha256.h5);
	ft_printf("%x%x%c", ssl->sha256.h6, ssl->sha256.h7, c);
}

void	ft_sha256_format_print(t_ssl *ssl)
{
	ft_sha256_print(ssl, '\n');
}


/*
** ft_bzero(&ssl->sha256, sizeof(t_ssl_sha256)); is the same as below:
** ft_bzero(&ssl->sha256, sizeof(ssl->sha256));
*/

void hash_message_sha256(t_ssl *ssl)
{
	ft_bzero(&ssl->sha256, sizeof(ssl->sha256));
	ft_sha256_init(ssl);
	ft_sha256_padding(ssl);
	ft_sha256_transformation(ssl);
	ft_sha256_format_print(ssl);

}


void hash_message(t_ssl *ssl)//, char *message_digest_algo, char *message_to_digest)
{
//	ssl->flag.p = ssl->flag.p;
//	unsigned int num[64];
//	int i = 0;

//	ft_printf("message digest algo: |%s|\n", ssl->message_digest_algo); // Remove
//	ft_printf("message to digest: |%s|\n", ssl->message_to_digest); // Remove
//	test_md5_table_k(ssl); // Remove
//	test_md5_table_s(); // Remove
//	test_md5_table_g(); // Remove
//	ft_bzero(&ssl->md5, sizeof(ssl->md5));
	
	if(ft_strcmp(ssl->message_digest_algo, "md5") == 0)
		hash_message_md5(ssl);
	else if(ft_strcmp(ssl->message_digest_algo, "sha256") == 0)
		hash_message_sha256(ssl);

}


/*
** print_error_message_dir prints error message for the directory
** If a file path is a directory it will still have a valid file descriptor of
** 1, but when the directory is opened with read, the return value of read will
** be -1 if it is a directory. strerror and errno are used the print the error
** message. "Is a directory"
*/

void error_message_dir(int fd, char *argv)
{
	ft_printf("ft_ssl: %s: %s\n", argv, strerror(errno));
//	fd = fd * 1;
	close(fd);
//	exit(EXIT_SUCCESS);
}

/*
** error messages calls onto eror_invalid_file_permission and
** error_message_dir functions.
** At the end closes the file descriptor
*/

bool error_messages(int fd, char *argv)
{
	char temp_buff[2];
	ssize_t return_of_read;

	return_of_read = 0;
	if(fd == -1)
	{
		error_invalid_file_permission(fd, argv);
		return(true);
	}
	return_of_read = read(fd, temp_buff, 1);
	if(return_of_read == -1)
	{
		error_message_dir(fd, argv);
		return(true);
	}
	close(fd);
	return(false);
}


/*
char *mini_gnl(int fd, char **argv)
{
	int buffer_len;
	char *big_buffer;
	char *final_str;

	buffer_len = calculate_buffer_length(fd, argv);
	big_buffer = malloc(sizeof(char) * (buffer_len + 1));
	final_str = malloc(sizeof(char) * (buffer_len + 1));	
	if(big_buffer == NULL || final_str == NULL)
		return("mini_gnl memory allocation failed\n");
	fd = open(argv[1], O_RDONLY);
	read(fd, big_buffer, buffer_len);
	big_buffer[buffer_len] = '\0';
	ft_strcpy(final_str, big_buffer);
	free(big_buffer);
	close(fd);
	return(final_str);
}
*/

/*
** Traverses through a file and counts the number of characters in the file.
** For example: will go through a file called alpha.txt, that has the following
** content:
** a
** bc
** def
** calculate_buffer_length will return 6.
*/

int calculate_buffer_length(int fd, char *argv)
{
	char buffer;
	int buffer_len;

	buffer_len = 0;
	fd = open(argv, O_RDONLY);
	while(read(fd, &buffer, 1) > 0)
		buffer_len++;
	close(fd);
	return(buffer_len);
}

/*
** Function mini_gnl reads a file and stores the content/text of that file to be
** used for hashing later.
*/


char *mini_gnl(int fd, char *argv)
{
	int buffer_len;
	char *big_buffer;

	buffer_len = calculate_buffer_length(fd, argv);
	big_buffer = malloc(sizeof(char) * (buffer_len + 1));
	if(big_buffer == NULL)
		return("mini_gnl memory allocation failed\n");
	fd = open(argv, O_RDONLY);
	read(fd, big_buffer, buffer_len);
	big_buffer[buffer_len] = '\0';
	close(fd);
	return(big_buffer);	
}


char *mini_gnl_stdin(void)
{
	char buffer[2];
	char *temp;
	char *new_string;
	int i;
	
	i = 1;
	new_string = malloc(sizeof(char) * (2));
	if(new_string == NULL)
		return("memory allocation failed in mini_gnl_stdin.\n");
	new_string[0] = 0;
	while((read(0, buffer, 1)) > 0)
	{
		buffer[i] = '\0';
		temp = new_string;
		new_string = ft_strjoin(temp, buffer);
		free(temp);
	}
	return(new_string);
}

bool is_ssl_flag_valid(char c)
{
	int i;

	i = 0;
	while(SSL_VALID_FLAG[i])
	{
		if(SSL_VALID_FLAG[i] == c)
			return(true);
		i++;
	}
	return(false);
}

void collect_ssl_flag(t_ssl *ssl, char c)
{
	if(c == 'p')
	{
		ssl->flag.p = true;
//		ssl->flag.count_of_p++;
	}
	else if(c == 'q')
		ssl->flag.q = true;
	else if(c == 'r')
		ssl->flag.r = true;
	else if(c == 's')
		ssl->flag.s = true;
}

/*
** ssl_exit_illegal_option is used when the flag is not one of the valid flag
** options -p, -q, -r, or -s.
*/

void ssl_exit_illegal_option(char c)
{
	ft_printf("ft_ssl: illegal option -- %c\n", c);
	ft_printf("usage: ft_ssl [-pqrs] [-s string] [files ...]\n");
	exit(EXIT_SUCCESS);
}
/*
** ft_option_requires_argument is used when an argument is not entered
** with -s flag.
** And the program in this case exits.
*/

void ft_option_requires_argument(char *digest_method)
{
	ft_printf("%s: option requires an argument -- s\n", digest_method);
	ft_printf("usage: %s [-pqr] [-s string] [files ...]\n", digest_method);
//		free(digest_method);
	exit(EXIT_SUCCESS);
}
/*
void store_message_to_digest_for_s(char *argv, t_ssl *ssl)
{
	char *message_to_digest;
	int len_of_message;

	len_of_message = ft_strlen(argv);
	message_to_digest = malloc(sizeof(char) * (len_of_message + 1));
	ft_strcpy(message_to_digest, argv);
	ft_printf("%s", message_to_digest);
	free(message_to_digest);
	ssl->flag.s = ssl->flag.s; // Just a filler for -Wall -Wextra -Werror
}
*/


/*
void store_hash_free_message(t_ssl *ssl, char *message_to_digest)
{
	ssl->message_to_digest = message_to_digest;
	hash_message(ssl);
	free(message_to_digest);
}
*/

/*
void	*ft_memalloc(size_t size)
{
	unsigned char	*memory;
	size_t			i;

	i = 0;
	memory = malloc(sizeof(unsigned char) * (size));
	if (memory == NULL || size > SIZE_T_MAX)
		return (NULL);
	else
		while (i <= size)
			memory[i++] = '\0';
	return (memory);
}
*/
void store_hash_free_message(t_ssl *ssl, char *message_to_digest)
{
	int message_len;

	message_len = ft_strlen(message_to_digest);
//	ssl->message_to_digest_len = message_len;
//	ft_printf("%d\n", message_len);
	ssl->message_to_digest = ft_memalloc(message_len + 1);
//	ssl->message_to_digest = malloc(sizeof(char) * (message_len + 1));
//	ft_printf(BGREEN"testing_u|%u|\n"NC, message_to_digest);
	if(ssl->message_to_digest == NULL)
		return;
//	ft_bzero(ssl->message_to_digest, message_len + 1);
//
	
	ssl->message_to_digest[0] = 0;
	ft_strcpy(ssl->message_to_digest, message_to_digest); // put it back on
//	ft_printf(BBLUE"%s\n"NC, message_to_digest);
	hash_message(ssl);
	free(message_to_digest);
	free(ssl->message_to_digest);
}


void ft_ssl_collect_flags_process_p(t_ssl *ssl)
{
	char *stdin_message_to_digest;
	char *empty_message_to_digest;
	char temp[1];

	ft_strcpy(temp, "");
	empty_message_to_digest = NULL;
	if(ssl->skip.mini_gnl_stdin_for_flag_p == false)
	{
		stdin_message_to_digest = mini_gnl_stdin();
//		ft_printf("%s", stdin_message_to_digest);
		store_hash_free_message(ssl, stdin_message_to_digest);
//		ssl->message_to_digest = stdin_message_to_digest;
//		hash_message(ssl);//, ssl->message_digest_algo, stdin_message_to_digest);
//		free(stdin_message_to_digest);
//		ssl->flag.count_of_p--;
		ssl->skip.mini_gnl_stdin_for_flag_p = true;
	}
	else if(ssl->skip.mini_gnl_stdin_for_flag_p == true)
	{

//		ft_printf("Comes into ft_ssl_collect_flags_process_p\n");
//		empty_message_to_digest = malloc(sizeof(char) * (1));
//		ft_bzero(empty_message_to_digest, 1);
//		ft_strcpy(empty_message_to_digest, temp);
//		ft_strcpy(empty_message_to_digest, "");
		empty_message_to_digest = ft_strdup("");
		store_hash_free_message(ssl, empty_message_to_digest);
//		ssl->message_to_digest = empty_message_to_digest;
//		while(ssl->flag.count_of_p)
//		{
//			hash_message(ssl);
//			ssl->flag.count_of_p--;
//		}
//		free(empty_message_to_digest);
	}
}

/*
** ft_ssl_collect_flags_process_s works as following
** ./ft_ssl md5 -s123
** String to hash appears right after -s without a space.
** Or if the -s flag is true but there are no arguments right after it.
** ./ft_ssl md5 -s
*/

void ft_ssl_collect_flags_process_s(char *message, t_ssl *ssl, int j, int argc)
{
	char *message_to_digest;

	if(ssl->flag.s == true && message[0] != '\0')
	{
//		message_to_digest = malloc(sizeof(char) * (ft_strlen(message) + 1));
//		ft_printf(BBLUE"|%s|%u|\n", message, message);
		message_to_digest = ft_memalloc(ft_strlen(message) + 1);
		ft_strcpy(message_to_digest, message);
		store_hash_free_message(ssl, message_to_digest);
//		ssl->message_to_digest = message_to_digest;
//		hash_message(ssl);//, ssl->message_digest_algo, message);
//		free(message_to_digest);
		ssl->flag.s = false;
	}
	else if(ssl->flag.s == true && j + 1 == argc)
	{

//		ft_printf(BBLUE"|%s|%u|\n", message, message);
		ft_option_requires_argument(ssl->message_digest_algo);
	}
}


void ft_ssl_collect_flags(char *argv, t_ssl *ssl, int j, int argc)
{
	int i;
//	char *stdin_message_to_digest;

	i = 1;
	while(argv[i])
	{
		if(is_ssl_flag_valid(argv[i]) == true)
		{
			collect_ssl_flag(ssl, argv[i]);
			if (ssl->flag.p == true)
				ft_ssl_collect_flags_process_p(ssl);
			if(ssl->flag.s == true)
				break;
		}
		else if(is_ssl_flag_valid(argv[i]) == false)
			ssl_exit_illegal_option(argv[i]);
		i++;
	}
//	if (ssl->flag.p == true)
//		ft_ssl_collect_flags_process_p(ssl);
	ft_ssl_collect_flags_process_s(argv + i + 1, ssl, j, argc);
/*
	if(ssl->flag.p == true)
	{
		if(ssl->skip.mini_gnl_stdin_for_flag_p == false)
		{
			stdin_message_to_digest = mini_gnl_stdin();
			hash_message(ssl->message_digest_algo, stdin_message_to_digest);
			free(stdin_message_to_digest);
			ssl->flag.count_of_p--;
			ssl->skip.mini_gnl_stdin_for_flag_p = true;
		}
		while(ssl->flag.count_of_p)
		{
			hash_message(ssl->message_digest_algo, "");
			ssl->flag.count_of_p--;
		}
	}
	if(ssl->flag.s == true && argv[i + 1] != '\0')
	{
		hash_message(ssl->message_digest_algo, argv + i + 1);
		ssl->flag.s = false;
	}
	else if(ssl->flag.s == true && j + 1 == argc)
		ft_option_requires_argument(ssl->message_digest_algo);
*/
}

/*
** Function is_there_p_or_s is used in function ft_ssl_parse_qr.
** Because ft_ssl_parse_qr is supposed to only pint and hash a string if
** q or r are true, and both p and s are false. Since functions ft_ssl_parse_qr
** and ft_ssl_parse_pqrs both rely on ft_ssl_collect_flags to collect flags, it
** is helpful to have is_there_p_or_s, so if 'p' or 's' are true then the pogram
** leaves ft_ssl_parse_qr to go to ft_ssl_parse_pqrs.
**
** Return Value: returns true if there is 'p' or 's'.
** Returns false if there is no 'p' or 's'
*/
bool is_there_p_or_s(char *argv)
{
	int i;

	i = 1;
	while(argv[i])
	{
		if(argv[i] == 'p' || argv[i] == 's')
			return(true);
		i++;
	}
	return(false);
}
bool is_md_algorithm_valid(char *str)
{
	if (ft_strcmp(str, "md5") == 0 || ft_strcmp(str, "sha224") == 0)
		return(true);
	else if (ft_strcmp(str, "sha256") == 0 || ft_strcmp(str, "sha384") == 0)
		return(true);
	else if (ft_strcmp(str, "sha512") == 0)
		return(true);
	return(false);
}

/*
** flag.p and flag.s are set equal to -1 because if -s or -p never appear in
** any of the arguments, but -q or -r are present then the program should be
** able to enter the standard input/stdin mode to read from stream.
*/
void ft_print_usage(char *buffer)
{
	ft_printf("ft_ssl:Error: '%s' is an invalid command.\n\n", buffer);
	ft_printf("Message Digest Commands:\n");
	ft_printf("md5\nsha224\nsha256\nsha384\nsha512\n\n");
}

void ft_initialize_ssl_flag(t_ssl *ssl)
{	
	ft_bzero(&ssl->flag, sizeof(ssl->flag));
	ft_bzero(&ssl->skip, sizeof(ssl->skip));
//	ssl->flag.count_of_p = 0;

//	ssl->skip_if = false;
//	ssl->skip_if_to_collect_flags = false;
//	ssl->skip_p_stdin = false;
//	ssl->skip_mini_gnl_stdin_for_flag_p = false;
//	ssl->flag.p_count = 0;
//	ssl->count_of_flag_p = 0;
//	ssl->skip_p = false;
//	ssl->flag.p = -1;
//	ssl->flag.s = -1;
//	ssl->flag.q = false;
//	ssl->flag.r = false;
}

void ft_ssl_parse_qr(int argc, char **argv)
{
	t_ssl ssl;
	char *message_to_digest;
	int i;

	i = 2;
//	ssl.md5_padded_message_len = 0;
	set_md5_to_zero(&ssl);
	ft_initialize_ssl_flag(&ssl);
	ssl.message_digest_algo = argv[1];
	while(i < argc)
	{
		if(is_there_p_or_s(argv[i]) == true)
			return;
		if(argv[i][0] == '-' && argv[i][1] != '\0')
			ft_ssl_collect_flags(argv[i], &ssl, i, argc);
		else
			return;
		i++;
	}
	message_to_digest = mini_gnl_stdin();
	store_hash_free_message(&ssl, message_to_digest);
//	ssl.message_to_digest = message_to_digest;
//	hash_message(&ssl);//, ssl.message_digest_algo, message_to_digest);
//	free(message_to_digest);
	exit(EXIT_SUCCESS);
}


void ft_ssl_parse_pqrs_no_dash_adjust_flags(t_ssl *ssl)
{
	if(ssl->flag.s == false && ssl->flag.p == false)
		ssl->skip.if_to_collect_flags = true;
	ssl->flag.s = false;
	ssl->flag.p = false;
//	ssl->flag.count_of_p = 0;
}

void ft_ssl_parse_pqrs_no_dash(char **argv, t_ssl *ssl, int i)
{
	char *message_to_digest;
	int fd;
	
	if(ssl->flag.s == true)
	{
		message_to_digest = malloc(sizeof(ft_strlen(argv[i]) + 1));
		ft_strcpy(message_to_digest, argv[i]);
		store_hash_free_message(ssl, message_to_digest);
//		ssl->message_to_digest = message_to_digest;
//		hash_message(ssl);//, ssl->message_digest_algo, argv[i]);
//		free(message_to_digest);
	}
	else if(ssl->flag.s == false)
	{
		fd = open(argv[i], O_RDONLY);
		if(error_messages(fd, argv[i]) == false)
		{
			ssl->file_name = argv[i];
			message_to_digest = mini_gnl(fd, argv[i]);
			store_hash_free_message(ssl, message_to_digest);
//			ssl->message_to_digest = message_to_digest;
//			hash_message(ssl);//, ssl->message_digest_algo, message_to_digest);
//			free(message_to_digest);
		}
		(fd) && (close(fd));
	}
	ft_ssl_parse_pqrs_no_dash_adjust_flags(ssl);
//	if(ssl->flag.s == false && ssl->flag.p == false)
//		ssl->skip.if_to_collect_flags = true;
//	ssl->flag.s = false;
//	ssl->flag.p = false;
//	ssl->flag.count_of_p = 0;
}

/*
** ssl.skip_if is false as long as 's' or 'p' flag appear.
** If in an argument 's' or 'p' flag dont appear than ssl.skip_if is enabled and
** set to true, so flags are no more collected.
*/
void ft_ssl_parse_pqrs(int argc, char **argv)
{
	t_ssl ssl;
	int i;

	i = 2;
//	ssl.md5_padded_message_len = 0;
	set_md5_to_zero(&ssl);
	ft_initialize_ssl_flag(&ssl);
	ssl.message_digest_algo = argv[1];
	while(i < argc)
	{
		if(argv[i][0] == '-' && argv[i][1] != '\0' && ssl.flag.s == false)
		{
			if(ssl.skip.if_to_collect_flags == false)	
				ft_ssl_collect_flags(argv[i], &ssl, i, argc);
		}
		else
			ft_ssl_parse_pqrs_no_dash(argv, &ssl, i);
		i++;
	}
}

void ft_ssl_parsing(int argc, char **argv)
{
	t_ssl ssl;
	char *message_to_digest;
	
//	ssl.md5_padded_message_len = 0;
	set_md5_to_zero(&ssl);
	if(is_md_algorithm_valid(argv[1]) == false)
	{
		ft_print_usage(argv[1]);
		exit(EXIT_SUCCESS);
	}
	else if(is_md_algorithm_valid(argv[1]) == true && argc == 2)
	{
		message_to_digest = mini_gnl_stdin();
		ssl.message_digest_algo = argv[1];
		store_hash_free_message(&ssl, message_to_digest);
//		ssl.message_to_digest = message_to_digest;
//		hash_message(&ssl);//, argv[1], message_to_digest);
//		free(message_to_digest);
	}
	else
	{
		ft_ssl_parse_qr(argc, argv);
		ft_ssl_parse_pqrs(argc, argv);
	}
/*
	t_ssl ssl;
	char *full_str;
	int i;
	int fd;

	i = 1;
	ft_initialize_ssl_flag(&ssl);
	ft_printf("|%d|\n", argc);
//	ft_ssl_parsing_for_qr(argc, argv);
	while(i < argc)
	{
		fd = open(argv[i], O_RDONLY);
		if(argv[i][0] == '-' && argv[i][1] != '\0')
		{
			ft_ssl_collect_flags(argv[i], &ssl);
		}
		else if(error_messages(fd, argv[i]) == false)
		{
			full_str = mini_gnl(fd, argv[i]);
			printf("ft_ssl (%s) = ",argv[i]);
			free(full_str);
		}	
		(fd) && (close(fd));
		i++;
	}
*/
}


/*
** Since the program should be able to exit out any time Ctrl + D is pressed,
** this function is created to check if the return of read is equal to 0.
** If enter is pressed, return_of_read is equal to 1.
** But if Ctrl+D is pressed, return_of_read is equal to 0. which will exit the
** program, just like how the original openssl does.
*/

void if_control_d_exit_program(int return_of_read)
{
	if(return_of_read == 0)
		exit(EXIT_SUCCESS);
}

/*
** read_stdin_loop reads the input from user if the only argument is ./ft_ssl.
**
** Program keeps on running under following conditions:
** 1. If enter is pressed.
** 2. If the digest message string is anything other than "md5", "sha224",
** "sha256", "sha384", "sha512"
**
** Program stops under following conditions:
** 1. If Control + D is pressed. And program exits
** 2. If digest message string is one of "md5", "sha224", "sha256", "sha384", or
** "sha512". And program continues to do the rest of the work.
*/

char *read_stdin_loop(char *message_digest_algorithm)
{
	int return_of_read;

	return_of_read = 0;
	while(1)
	{	
		ft_printf("ft_SSL> ");
		message_digest_algorithm[0] = 0;
		return_of_read = read(0, message_digest_algorithm, 8);
		if(return_of_read > 1)
		{
			message_digest_algorithm[return_of_read - 1] = '\0';
			if(is_md_algorithm_valid(message_digest_algorithm) == true)
			{
				return(message_digest_algorithm);
//				break;
			}
			else
				ft_print_usage(message_digest_algorithm);
		}
		if_control_d_exit_program(return_of_read);
//		if(return_of_read == 0)
//			exit(EXIT_SUCCESS);
	}
}

//void handle_stdin(void)
void handle_stdin(t_ssl *ssl)
{
	char message_digest_algo[8];
	char *message_to_digest;
	
//	ssl->md5.padded_message_len = 0;
	set_md5_to_zero(ssl);
	read_stdin_loop(message_digest_algo);
	message_to_digest = mini_gnl_stdin();
	ssl->message_digest_algo = message_digest_algo;
	store_hash_free_message(ssl, message_to_digest);
//	ssl->message_to_digest = message_to_digest;
//	hash_message(ssl);//message_digest_algo, message_to_digest);
//	free(message_to_digest);

//	char *md_command;
//	ft_printf("%s", message_digest_buffer);
//	ft_printf("ft_SSL> ");
//	md_command = is_md_command_valid();
//	check_if // -1 -> strcmp != 0 and usage, 0i, 1
//	string = mini_gnl_stdin();

//	system(string);
//	if(ft_strcmp(string, "md5") == 0)
//		printf("%s", string); ///////////////////
//	free(string);       ///////////////
//	char buffer;

//	while(read(0, &buffer, 1) > 0)
//		ft_printf("%c", buffer);

//	str = mini_gnl(0, argv[1]);
	
//	printf("%s", str);
//	while(1)
//	{
//		str = argv[1];
//	}
//	printf("%s", str);
}

int main(int argc, char *argv[])
{
	t_ssl ssl;


//	ft_printf(BYELLOW"|%s|"NC, argv[1]);
//	ft_printf(BYELLOW"%u|\n"NC, argv[1]);
//	ft_printf(BYELLOW"|%s|"NC, argv[2]);
//	ft_printf(BYELLOW"%u|\n"NC, argv[2]);
//	ft_printf(BYELLOW"|%s|"NC, argv[3]);
//	ft_printf(BYELLOW"%u|\n"NC, argv[3]);
//	ft_printf(BYELLOW"|%s|"NC, argv[4]);
//	ft_printf(BYELLOW"%u|\n"NC, argv[4]);





//	int fd;

//	fd = open(argv[1], O_RDONLY);

	if(argc == 1)
		handle_stdin(&ssl);
	else if(argc > 1)
		ft_ssl_parsing(argc, argv);
	
//	while(1);
//	system("leaks ft_ssl");
//	while(1);

/*
	if(argc >= 1)
	{
		if(fd == -1)
			ft_printf("%s\n", strerror(errno));
		else if(fd == 3)
			ft_printf("%s\n", strerror(errno));
		printf("%s\n", strerror(fd));
		ft_printf("file desciptor:|%d|\n", fd);
	}
*/
//	num = argc;
//	ft_printf("Number of arguments:|%d|\n", num);
//	ft_printf("%s", argv[0]);

//	ft_printf("|This is just a test for %*d_ft_ssl|\n", 0, 42);
}
