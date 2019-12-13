/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_sha256_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:08:44 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/12 18:09:27 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

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
