/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:41:06 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/11 21:39:15 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** print_error_messages takes a 2d array and if the file descriptor is -1, then
** the error message is printed.
** File desciptor will be -1 under 1 of 2 conditions:
** 1. A file path is an invalid file path. "No such file or directory"
** 2. A file has permission denied access. "Permission denied"
*/

void print_error_message(int fd, char **argv)
{
	ft_printf("ft_ssl1: %s: %s\n", argv[1], strerror(errno));
	close(fd);
	exit(EXIT_SUCCESS);
}

/*
** print_error_message_dir prints error message for the directory
** If a file path is a directory it will still have a valid file descriptor of
** 1, but when the directory is opened with read, the return value of read will
** be -1 if it is a directory. strerror and errno are used the print the error
** message. "Is a directory"
*/

void print_error_message_dir(int fd, char **argv)
{
	ft_printf("ft_ssl: %s: %s\n", argv[1], strerror(errno));
	close(fd);
	exit(EXIT_SUCCESS);
}

void ft_ssl_parsing(int fd, char **argv)
{
	char temp_buff[2];
	ssize_t return_of_read;

	return_of_read = 0;
	if(fd == -1)
		print_error_message(fd, argv);
	return_of_read = read(fd, temp_buff, 1);
	if(return_of_read == -1)
		print_error_message_dir(fd, argv);

//	return_of_read = read(fd, temp_buff, 1);
//	ft_printf("|%d|\n", return_of_read);
}

int main(int argc, char *argv[])
{
	int fd;

	fd = open(argv[1], O_RDONLY);

	if(argc > 0)
		ft_ssl_parsing(fd, argv);

/*
	if(argc >= 1)
	{
		if(fd == -1)
			ft_printf("%s\n", strerror(errno));
		else if(fd == 3)
			ft_printf("%s\n", strerror(errno));
		printf("%s\n", strerror(fd));
		ft_printf("file desciptor:|%d|\n", fd);
	}
*/
//	num = argc;
//	ft_printf("Number of arguments:|%d|\n", num);
//	ft_printf("%s", argv[0]);

//	ft_printf("|This is just a test for %*d_ft_ssl|\n", 0, 42);
}
