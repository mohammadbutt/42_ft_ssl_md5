/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_error_messages.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 22:36:42 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/11 22:41:43 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	error_invalid_file_permission(t_ssl *ssl, int fd, char *argv)
{
	char *algo;

	algo = ssl->message_digest_algo;
	ft_printf(BRED"%s: %s: %s\n"NC, algo, argv, strerror(errno));
	close(fd);
}

/*
** print_error_message_dir prints error message for the directory
** If a file path is a directory it will still have a valid file descriptor of
** 1, but when the directory is opened with read, the return value of read will
** be -1 if it is a directory. strerror and errno are used the print the error
** message. "Is a directory"
*/

void	error_message_dir(t_ssl *ssl, int fd, char *argv)
{
	char	*algo;

	algo = ssl->message_digest_algo;
	ft_printf(BYELLOW"%s: %s: %s\n"NC, algo, argv, strerror(errno));
	close(fd);
}

/*
** print_error_messages takes a 2d array and if the file descriptor is -1, then
** the error message is printed.
** File desciptor will be -1 under 1 of 2 conditions:
** 1. A file path is an invalid file path. "No such file or directory"
** 2. A file has permission denied access. "Permission denied"
**
** error messages calls onto eror_invalid_file_permission and
** error_message_dir functions.
** At the end closes the file descriptor
*/

bool	error_messages(t_ssl *ssl, int fd, char *argv)
{
	char	temp_buff[2];
	ssize_t	return_of_read;

	return_of_read = 0;
	if (fd == -1)
	{
		error_invalid_file_permission(ssl, fd, argv);
		return (true);
	}
	return_of_read = read(fd, temp_buff, 1);
	if (return_of_read == -1)
	{
		error_message_dir(ssl, fd, argv);
		return (true);
	}
	close(fd);
	return (false);
}
