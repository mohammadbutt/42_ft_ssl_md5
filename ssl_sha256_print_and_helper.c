/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_sha256_print_and_helper.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:45:59 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/12 17:54:03 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

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
** Adding sha-256 and sha-512 functions
**
** function rotate_right_32_bit is used for sha-224 and sha-256
**
** function rotate_right_64_bit is used for sha-384 and sha-512
*/

uint32_t	rotate_right_32bit(uint32_t value, uint32_t rotate_n_bits)
{
	uint32_t new_value;

	new_value = ((value >> rotate_n_bits) | (value << (32 - rotate_n_bits)));
	return (new_value);
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
	return (new_value);
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

uint32_t	ft_swap_32bit(uint32_t value)
{
	uint32_t swapped;

	swapped = 0;
	swapped |= (value & 0x000000FF) << 24;
	swapped |= (value & 0x0000FF00) << 8;
	swapped |= (value & 0x00FF0000) >> 8;
	swapped |= (value & 0xFF000000) >> 24;
	return (swapped);
}

void		ft_sha256_print(t_ssl *ssl, char c)
{
	char *algo;

	algo = ssl->message_digest_algo;
	ft_printf("%08x%08x%08x", ssl->sha256.h0, ssl->sha256.h1, ssl->sha256.h2);
	ft_printf("%08x%08x%08x", ssl->sha256.h3, ssl->sha256.h4, ssl->sha256.h5);
	ft_printf("%08x", ssl->sha256.h6);
	if (ft_strcmp(algo, "sha224") == 0 || ft_strcmp(algo, "SHA224") == 0)
		ft_printf("%c", c);
	else if (ft_strcmp(algo, "sha256") == 0 || ft_strcmp(algo, "SHA256") == 0)
		ft_printf("%08x%c", ssl->sha256.h7, c);
}

void		ft_sha256_format_print(t_ssl *ssl, char *algo_name)
{
	if (ssl->flag.r == true && ssl->flag.s == true)
	{
		ft_sha256_print(ssl, ' ');
		ft_printf("\"%s\"\n", ssl->message_to_digest);
	}
	else if (ssl->flag.p == true || ssl->flag.ft_stdin == true)
	{
		ft_sha256_print(ssl, '\n');
		(ssl->flag.ft_stdin == true) && (ft_printf("ft_SSL> "));
		ssl->flag.p = false;
	}
	else if (ssl->flag.r == false && ssl->flag.s == true)
	{
		ft_printf("%s (\"%s\") = ", algo_name, ssl->message_to_digest);
		ft_sha256_print(ssl, '\n');
	}
	else if (ssl->flag.s == false)
	{
		ft_printf("%s (%s) = ", algo_name, ssl->file_name);
		ft_sha256_print(ssl, '\n');
	}
}
