/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_collect_flags.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 22:08:13 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/11 22:20:34 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

bool	is_ssl_flag_valid(char c)
{
	int i;

	i = 0;
	while (SSL_VALID_FLAG[i])
	{
		if (SSL_VALID_FLAG[i] == c)
			return (true);
		i++;
	}
	return (false);
}

void	collect_ssl_flag(t_ssl *ssl, char c)
{
	if (c == 'p')
		ssl->flag.p = true;
	else if (c == 'q')
		ssl->flag.q = true;
	else if (c == 'r')
		ssl->flag.r = true;
	else if (c == 's')
		ssl->flag.s = true;
}

void	ft_ssl_collect_flags_process_p(t_ssl *ssl)
{
	char	*stdin_message_to_digest;
	char	*empty_message_to_digest;
	char	temp[1];

	ft_strcpy(temp, "");
	empty_message_to_digest = NULL;
	if (ssl->skip.mini_gnl_stdin_for_flag_p == false)
	{
		stdin_message_to_digest = mini_gnl_stdin();
		store_hash_free_message(ssl, stdin_message_to_digest);
		ssl->skip.mini_gnl_stdin_for_flag_p = true;
	}
	else if (ssl->skip.mini_gnl_stdin_for_flag_p == true)
	{
		empty_message_to_digest = ft_strdup("");
		store_hash_free_message(ssl, empty_message_to_digest);
	}
}

/*
** ft_ssl_collect_flags_process_s works as following
** ./ft_ssl md5 -s123
** String to hash appears right after -s without a space.
** Or if the -s flag is true but there are no arguments right after it.
** ./ft_ssl md5 -s
*/

void	ft_ssl_collect_flags_process_s(char *message, t_ssl *ssl, int j,
		int argc)
{
	char *message_to_digest;

	if (ssl->flag.s == true && message[0] != '\0')
	{
		message_to_digest = ft_memalloc(ft_strlen(message) + 1);
		ft_strcpy(message_to_digest, message);
		store_hash_free_message(ssl, message_to_digest);
		ssl->flag.s = false;
	}
	else if (ssl->flag.s == true && j + 1 == argc)
		ft_option_requires_argument(ssl->message_digest_algo);
}

void	ft_ssl_collect_flags(char *argv, t_ssl *ssl, int j, int argc)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (is_ssl_flag_valid(argv[i]) == true)
		{
			collect_ssl_flag(ssl, argv[i]);
			if (ssl->flag.p == true)
				ft_ssl_collect_flags_process_p(ssl);
			if (ssl->flag.s == true)
				break ;
		}
		else if (is_ssl_flag_valid(argv[i]) == false)
			ssl_exit_illegal_option(argv[i]);
		i++;
	}
	ft_ssl_collect_flags_process_s(argv + i + 1, ssl, j, argc);
}
