/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_hash_message_sha224.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:56:49 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/12 17:57:59 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	ft_sha224_init(t_ssl *ssl)
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

void	hash_message_sha224(t_ssl *ssl)
{
	ft_bzero(&ssl->sha256, sizeof(ssl->sha256));
	ft_sha224_init(ssl);
	ft_sha256_padding(ssl);
	ft_sha256_transformation(ssl);
	if (ssl->flag.ft_stdin == true || ssl->flag.q == true)
		ft_sha256_print(ssl, '\n');
	else
		ft_sha256_format_print(ssl, "SHA224");
}
