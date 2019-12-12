/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 22:25:25 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/11 22:30:08 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** Traverses through a file and counts the number of characters in the file.
** For example: will go through a file called alpha.txt, that has the following
** content:
** a
** bc
** def
** calculate_buffer_length will return 6.
** Return of calculate_buffer_length is used to allocate memory to read the file
** in one go.
*/

int		calculate_buffer_length(int fd, char *argv)
{
	char	buffer;
	int		buffer_len;

	buffer_len = 0;
	fd = open(argv, O_RDONLY);
	while (read(fd, &buffer, 1) > 0)
		buffer_len++;
	close(fd);
	return (buffer_len);
}

/*
** Function mini_gnl reads a file and stores the content/text of that file to be
** used for hashing later.
*/

char	*mini_gnl(int fd, char *argv)
{
	int		buffer_len;
	char	*big_buffer;

	buffer_len = calculate_buffer_length(fd, argv);
	big_buffer = malloc(sizeof(char) * (buffer_len + 1));
	if (big_buffer == NULL)
		return ("mini_gnl memory allocation failed\n");
	fd = open(argv, O_RDONLY);
	read(fd, big_buffer, buffer_len);
	big_buffer[buffer_len] = '\0';
	close(fd);
	return (big_buffer);
}

char	*mini_gnl_stdin(void)
{
	char	buffer[2];
	char	*temp;
	char	*new_string;
	int		i;

	i = 1;
	new_string = malloc(sizeof(char) * (2));
	if (new_string == NULL)
		return ("memory allocation failed in mini_gnl_stdin.\n");
	new_string[0] = 0;
	while ((read(0, buffer, 1)) > 0)
	{
		buffer[i] = '\0';
		temp = new_string;
		new_string = ft_strjoin(temp, buffer);
		free(temp);
	}
	return (new_string);
}
