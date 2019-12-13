/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_usage_and_option.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 22:47:20 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/11 22:48:29 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** ssl_exit_illegal_option is used when the flag is not one of the valid flag
** options -p, -q, -r, or -s.
*/

void	ssl_exit_illegal_option(char c)
{
	ft_printf("ft_ssl: illegal option -- %c\n", c);
	ft_printf("usage: ft_ssl [-pqrs] [-s string] [files ...]\n");
	exit(EXIT_SUCCESS);
}

/*
** ft_option_requires_argument is used when an argument is not entered
** with -s flag.
** And the program in this case exits.
*/

void	ft_option_requires_argument(char *digest_method)
{
	ft_printf("%s: option requires an argument -- s\n", digest_method);
	ft_printf("usage: %s [-pqr] [-s string] [files ...]\n", digest_method);
	exit(EXIT_SUCCESS);
}

void	ft_print_usage(char *buffer)
{
	ft_printf("ft_ssl:Error: '%s' is an invalid command.\n\n", buffer);
	ft_printf("Message Digest Commands:\n");
	ft_printf("md5\nsha224\nsha256\nsha384\nsha512\n\n");
}
