/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:41:06 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/11 20:13:36 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** print_error_messages takes a 2d array and if the file descriptor is -1, then
** the error message is printed.
** File desciptor will be -1 under 1 of 2 conditions:
** 1. A file path is an invalid file path.
** 2. A file has permission denied access.
** 
*/
void print_error_messages(char **argv)
{
	ft_printf("ft_ssl: %s: %s\n", argv[1], strerror(errno));
	exit(EXIT_SUCCESS);
}

void ft_ssl_parsing(int fd, char **argv)
{
	if(fd == -1)
		print_error_messages(argv);
}

int main(int argc, char *argv[])
{
	int fd;

	fd = open(argv[1], O_RDONLY);

	ft_ssl_parsing(fd, argv);

	if(argc >= 1)
	{
		if(fd == -1)
			ft_printf("%s\n", strerror(errno));
		else if(fd == 3)
			ft_printf("%s\n", strerror(errno));
		printf("%s\n", strerror(fd));
		ft_printf("file desciptor:|%d|\n", fd);
	}

//	num = argc;
//	ft_printf("Number of arguments:|%d|\n", num);
//	ft_printf("%s", argv[0]);

//	ft_printf("|This is just a test for %*d_ft_ssl|\n", 0, 42);
}
