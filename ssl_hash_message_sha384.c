/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_hash_message_sha384.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:59:54 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/12 19:00:23 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	ft_sha384_init(t_ssl *ssl)
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

void	hash_message_sha384(t_ssl *ssl)
{
	ft_bzero(&ssl->sha512, sizeof(ssl->sha512));
	ft_sha384_init(ssl);
	ft_sha512_padding(ssl);
	ft_sha512_transformation(ssl);
	if (ssl->flag.ft_stdin == true || ssl->flag.q == true)
		ft_sha512_print(ssl, '\n');
	else
		ft_sha512_format_print(ssl, "SHA384");
}
