/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_store_hash_free_message.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 12:55:06 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/12 19:44:24 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** Hash message without dispatch_table
**
**void hash_message(t_ssl *ssl)
**{
**	char *algo;
**
**	algo = ssl->message_digest_algo;
**	if (ft_strcmp(algo, "md5") == 0 || ft_strcmp(algo, "MD5") == 0)
**		hash_message_md5(ssl);
**	else if (ft_strcmp(algo, "sha224") == 0 || ft_strcmp(algo, "SHA224") == 0)
**		hash_message_sha224(ssl);
**	else if (ft_strcmp(algo, "sha256") == 0 || ft_strcmp(algo, "SHA256") == 0)
**		hash_message_sha256(ssl);
**	else if (ft_strcmp(algo, "sha384") == 0 || ft_strcmp(algo, "SHA384") == 0)
**		hash_message_sha384(ssl);
**	else if (ft_strcmp(algo, "sha512") == 0 || ft_strcmp(algo, "SHA512") == 0)
**		hash_message_sha512(ssl);
**}
*/

void	hash_message(t_ssl *ssl)
{
	char	*algo;
	int		i;

	algo = ssl->message_digest_algo;
	i = 0;
	if (ft_strcmp(algo, "md5") == 0 || ft_strcmp(algo, "MD5") == 0)
		i = 0;
	else if (ft_strcmp(algo, "sha224") == 0 || ft_strcmp(algo, "SHA224") == 0)
		i = 1;
	else if (ft_strcmp(algo, "sha256") == 0 || ft_strcmp(algo, "SHA256") == 0)
		i = 2;
	else if (ft_strcmp(algo, "sha384") == 0 || ft_strcmp(algo, "SHA384") == 0)
		i = 3;
	else if (ft_strcmp(algo, "sha512") == 0 || ft_strcmp(algo, "SHA512") == 0)
		i = 4;
	g_ssl_dispatch_table[i](ssl);
}

void	store_hash_free_message(t_ssl *ssl, char *message_to_digest)
{
	int message_len;

	message_len = ft_strlen(message_to_digest);
	ssl->message_to_digest = ft_memalloc(message_len + 1);
	if (ssl->message_to_digest == NULL)
		return ;
	ssl->message_to_digest[0] = 0;
	ft_strcpy(ssl->message_to_digest, message_to_digest);
	hash_message(ssl);
	free(message_to_digest);
	free(ssl->message_to_digest);
}
