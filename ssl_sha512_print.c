/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_sha512_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:52:18 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/12 18:55:01 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	ft_sha512_print(t_ssl *ssl, char c)
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
	if (ssl->flag.r == true && ssl->flag.s == true)
	{
		ft_sha512_print(ssl, ' ');
		ft_printf("\"%s\"\n", ssl->message_to_digest);
	}
	else if (ssl->flag.p == true || ssl->flag.ft_stdin == true)
	{
		ft_sha512_print(ssl, '\n');
		(ssl->flag.ft_stdin == true) && (ft_printf("ft_SSL> "));
		ssl->flag.p = false;
	}
	else if (ssl->flag.r == false && ssl->flag.s == true)
	{
		ft_printf("%s (\"%s\") = ", algo_name, ssl->message_to_digest);
		ft_sha512_print(ssl, '\n');
	}
	else if (ssl->flag.s == false)
	{
		ft_printf("%s (%s) = ", algo_name, ssl->file_name);
		ft_sha512_print(ssl, '\n');
	}
}
