/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_parse_pqrs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 21:39:04 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/15 16:38:37 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	ft_ssl_parse_qr(int argc, char **argv)
{
	t_ssl	ssl;
	char	*message_to_digest;
	int		i;

	i = 2;
	ft_bzero(&ssl, sizeof(t_ssl));
	ssl.message_digest_algo = argv[1];
	while (i < argc)
	{
		if (is_there_p_or_s(argv[i]) == true)
			return ;
		if (argv[i][0] == '-' && argv[i][1] != '\0')
			ft_ssl_collect_flags(argv[i], &ssl, i, argc);
		else
			return ;
		i++;
	}
	message_to_digest = mini_gnl_stdin();
	store_hash_free_message(&ssl, message_to_digest);
}

void	ft_ssl_parse_pqrs_no_dash_adjust_flags(t_ssl *ssl)
{
	if (ssl->flag.s == false && ssl->flag.p == false)
		ssl->skip.if_to_collect_flags = true;
	ssl->flag.s = false;
	ssl->flag.p = false;
}

void	ft_ssl_parse_pqrs_no_dash(char **argv, t_ssl *ssl, int i)
{
	char	*message_to_digest;
	int		fd;

	if (ssl->flag.s == true)
	{
		message_to_digest = malloc(sizeof(char) * (ft_strlen(argv[i]) + 1));
		ft_strcpy(message_to_digest, argv[i]);
		store_hash_free_message(ssl, message_to_digest);
	}
	else if (ssl->flag.s == false)
	{
		fd = open(argv[i], O_RDONLY);
		if (error_messages(ssl, fd, argv[i]) == false)
		{
			ssl->file_name = argv[i];
			message_to_digest = mini_gnl(fd, argv[i]);
			store_hash_free_message(ssl, message_to_digest);
			ssl->skip.if_to_collect_flags = true;
		}
		(fd) && (close(fd));
	}
	ft_ssl_parse_pqrs_no_dash_adjust_flags(ssl);
}

/*
** ssl.skip.if_to_collect_flags is false as long as 's' or 'p' flag appear.
** If 's' or 'p' flag dont appear in argument then ssl.skip.if_to_collect_flag
** is enabled and set to true, so flags are not collected anymore.
*/

void	ft_ssl_parse_pqrs(int argc, char **argv)
{
	t_ssl	ssl;
	int		i;

	i = 2;
	ft_bzero(&ssl, sizeof(t_ssl));
	ft_initialize_ssl_flag(&ssl);
	ssl.message_digest_algo = argv[1];
	while (i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] != '\0' && ssl.flag.s == false)
		{
			if (ssl.skip.if_to_collect_flags == false)
				ft_ssl_collect_flags(argv[i], &ssl, i, argc);
			else
				ft_ssl_parse_pqrs_no_dash(argv, &ssl, i);
		}
		else
			ft_ssl_parse_pqrs_no_dash(argv, &ssl, i);
		i++;
	}
}

void	ft_ssl_parsing(int argc, char **argv)
{
	t_ssl	ssl;
	char	*message_to_digest;

	ft_bzero(&ssl, sizeof(t_ssl));
	if (is_md_algorithm_valid(argv[1]) == false)
	{
		ft_print_usage(argv[1]);
		exit(EXIT_SUCCESS);
	}
	else if (is_md_algorithm_valid(argv[1]) == true && argc == 2)
	{
		message_to_digest = mini_gnl_stdin();
		ssl.message_digest_algo = argv[1];
		ssl.flag.ft_stdin = true;
		store_hash_free_message(&ssl, message_to_digest);
	}
	else
	{
		ft_ssl_parse_qr(argc, argv);
		ft_ssl_parse_pqrs(argc, argv);
	}
}
