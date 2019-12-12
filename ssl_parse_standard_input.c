/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_parse_standard_input.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 20:13:02 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/11 20:24:13 by mbutt            ###   ########.fr       */
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
