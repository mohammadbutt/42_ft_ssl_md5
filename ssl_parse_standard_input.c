/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_parse_standard_input.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 20:13:02 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/11 22:20:47 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** read_stdin_loop reads the input from user if the only argument is ./ft_ssl.
**
** Program keeps on running under following conditions:
** 1. If enter is pressed.
** 2. If the digest message string is anything other than "md5", "sha224",
** "sha256", "sha384", "sha512"
**
** Program stops under following conditions:
** 1. If Control + D is pressed. And program exits
** 2. If digest message string is one of "md5", "sha224", "sha256", "sha384", or
** "sha512". And program continues to do the rest of the work.
*/

char	*read_stdin_loop(char *message_digest_algorithm)
{
	int	return_of_read;

	return_of_read = 0;
	while (1)
	{
		ft_printf("ft_SSL> ");
		message_digest_algorithm[0] = 0;
		return_of_read = read(0, message_digest_algorithm, 8);
		if (return_of_read > 1)
		{
			message_digest_algorithm[return_of_read - 1] = '\0';
			if (is_md_algorithm_valid(message_digest_algorithm) == true)
				return (message_digest_algorithm);
			else
				ft_print_usage(message_digest_algorithm);
		}
		if_control_d_exit_program(return_of_read);
	}
}

void	handle_stdin(t_ssl *ssl)
{
	char	message_digest_algo[8];
	char	*message_to_digest;

	ft_bzero(ssl, sizeof(t_ssl));
	read_stdin_loop(message_digest_algo);
	message_to_digest = mini_gnl_stdin();
	ssl->flag.ft_stdin = true;
	ssl->message_digest_algo = message_digest_algo;
	store_hash_free_message(ssl, message_to_digest);
}

/*
** Since the program should be able to exit out any time Ctrl + D is pressed,
** this function is created to check if the return of read is equal to 0.
** If enter is pressed, return_of_read is equal to 1.
** But if Ctrl+D is pressed, return_of_read is equal to 0. which will exit the
** program, just like how the original openssl does.
*/

void	if_control_d_exit_program(int return_of_read)
{
	if (return_of_read == 0)
		exit(EXIT_SUCCESS);
}

bool	is_md_algorithm_valid(char *str)
{
	if (ft_strcmp(str, "md5") == 0 || ft_strcmp(str, "MD5") == 0)
		return (true);
	else if (ft_strcmp(str, "sha224") == 0 || ft_strcmp(str, "SHA224") == 0)
		return (true);
	else if (ft_strcmp(str, "sha256") == 0 || ft_strcmp(str, "SHA256") == 0)
		return (true);
	else if (ft_strcmp(str, "sha384") == 0 || ft_strcmp(str, "SHA384") == 0)
		return (true);
	else if (ft_strcmp(str, "sha512") == 0 || ft_strcmp(str, "SHA512") == 0)
		return (true);
	return (false);
}

/*
** Function is_there_p_or_s is used in function ft_ssl_parse_qr.
** Because ft_ssl_parse_qr is supposed to only pint and hash a string if
** q or r are true, and both p and s are false.
** Since functions ft_ssl_parse_qr and ft_ssl_parse_pqrs both rely on
** ft_ssl_collect_flags to collect flags, it is helpful to have is_there_p_or_s,
** so if 'p' or 's' are true then the pogram leaves ft_ssl_parse_qr to go to
** ft_ssl_parse_pqrs.
**
** Return Value: returns true if there is 'p' or 's'.
** Returns false if there is no 'p' or 's'
*/

bool	is_there_p_or_s(char *argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (argv[i] == 'p' || argv[i] == 's')
			return (true);
		i++;
	}
	return (false);
}
