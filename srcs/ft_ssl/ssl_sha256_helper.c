/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_sha256_print_and_helper.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:45:59 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/12 18:15:28 by mbutt            ###   ########.fr       */
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

void		ft_bzero_num_array_32bit(uint32_t *num, uint32_t number_of_elements)
{
	uint32_t i;

	i = 0;
	while (i < number_of_elements)
		num[i++] = 0;
}

uint32_t	calculate_ssl_padding_32bit(uint32_t padding)
{
	uint32_t ft_64_byte;
	uint32_t ft_56_byte;

	ft_64_byte = 512 / 8;
	ft_56_byte = 448 / 8;
	if (padding % ft_64_byte == ft_56_byte)
		padding = padding + ft_64_byte;
	else
		while (padding % ft_64_byte != ft_56_byte)
			padding++;
	return (padding);
}
