/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:18:06 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/12 18:55:11 by mbutt            ###   ########.fr       */
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
*/
