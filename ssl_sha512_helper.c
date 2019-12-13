/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_sha512_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:45:27 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/12 18:50:45 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t	rotate_right_64bit(uint64_t value, uint64_t rotate_n_bits)
{
	uint64_t new_value;

	new_value = ((value >> rotate_n_bits) | (value << (64 - rotate_n_bits)));
	return (new_value);
}

uint64_t	shift_right_64bit(uint64_t value, uint64_t shift_n_bits)
{
	uint64_t new_value;

	new_value = value >> shift_n_bits;
	return (new_value);
}

/*
** Swaps bits of a uint64_t number
*/

uint64_t	ft_swap_64bit(uint64_t value)
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
	return (swapped);
}

void		ft_bzero_num_array_64bit(uint64_t *num, uint64_t number_of_elements)
{
	uint64_t i;

	i = 0;
	while (i < number_of_elements)
		num[i++] = 0;
}

uint64_t	calculate_ssl_padding_64bit(uint64_t padding)
{
	uint64_t	ft_128_byte;
	uint64_t	ft_112_byte;

	ft_128_byte = (512 * 2) / 8;
	ft_112_byte = (448 * 2) / 8;
	if (padding % ft_128_byte == ft_112_byte)
		padding = padding + ft_128_byte;
	else
		while (padding % ft_128_byte != ft_112_byte)
			padding++;
	return (padding);
}
