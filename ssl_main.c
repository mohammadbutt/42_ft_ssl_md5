/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:02:34 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/12 21:01:38 by mbutt            ###   ########.fr       */
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

void error_invalid_file_permission(int fd, char **argv)
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

void error_message_dir(int fd, char **argv)
{
	ft_printf("ft_ssl: %s: %s\n", argv[1], strerror(errno));
	close(fd);
	exit(EXIT_SUCCESS);
}

/*
** error messages calls onto eror_invalid_file_permission and
** error_message_dir functions.
** At the end closes the file descriptor
*/

void error_messages(int fd, char **argv)
{
	char temp_buff[2];
	ssize_t return_of_read;

	return_of_read = 0;
	if(fd == -1)
		error_invalid_file_permission(fd, argv);
	return_of_read = read(fd, temp_buff, 1);
	if(return_of_read == -1)
		error_message_dir(fd, argv);
	close(fd);
}
/*
** Function mini_gnl reads a file and stores the content/text of that file to be
** used for hasing later.
*/

/*
char *mini_gnl(int fd, char **argv)
{
	char placeholder[2];
	char *temp;
	char *s;
	int i;
	char *temp_pointer;
	int len;

	temp = NULL;
	i = 2;
	fd = open(argv[1], O_RDONLY);
//	s = malloc(sizeof(char) * (2));
//	if(s == NULL)
//		return("Malloc Error");
	while(read(fd, placeholder, 1) > 0)
	{
		placeholder[1] = '\0';
		ft_printf("%s", placeholder);
		s = malloc(sizeof(char) * (i + 1));
		temp = malloc(sizeof(char) * (i + 1));
		if(s == NULL || temp == NULL)
			return("Malloc Error inside while loop");
		ft_strcat(temp, placeholder);
		i++;
		s[i] = '\0';
		temp_pointer = s;
		if(s)
			free(s);
		if (temp)
			free(temp);
//		i++;
	}
	len = 0;
	len = ft_strlen(temp_pointer + 1);
	s = malloc(sizeof(char) * (len + 1));
	ft_strcpy(s, temp);
//	len = ft_strlen(temp_str2);
//	temp_str2[i] = '\0';
//	full_string = malloc(sizeof(char) * (i + 1));
//	ft_strcpy(full_string, temp_str2);
//	ft_printf("%s", temp_str2);
//	ft_printf("%s", full_string);
//	ft_printf("%s", temp);
//	ft_printf("%s", s);
	return(s);

}
*/

/*
char *mini_gnl(int fd, char **argv)
{
	int i;
	char buffer;
	char *str;
	char *pointer;

	i = 1;
	pointer = NULL;
	fd = open(argv[1], O_RDONLY);
	while(read(fd, &buffer, 1) > 0)
	{
//		ft_printf("%c", buffer);
		str = malloc(sizeof(char) * (i + 1));
//		ft_printf("|%s|", pointer);
		if(i > 1)
			ft_strcpy(str, pointer);
		else
			ft_strcpy(str, &buffer);
		str[i - 1] = buffer;
		str[i] = '\0';
//		ft_strcat(str, &buffer);
//		ft_strcpy(str, pointer);
		pointer = str;
		ft_printf("|%s|\n", pointer);
		i++;
		free(str);
//		ft_printf("%c", buffer);
	}
	ft_printf("%s", pointer);
	close(fd);
	str = malloc(sizeof(char) * (i + 1));
	ft_strcpy(str, pointer);
	return(str);
}
*/

/*
** Traverses through a file and counts the number of characters in the file.
** For example: will go through a file called alpha.txt, that has the following
** content:
** a
** bc
** def
** calculate_buffer_length will return 6.
*/

int calculate_buffer_length(int fd, char **argv)
{
	char buffer;
	int buffer_len;

	buffer_len = 0;
	fd = open(argv[1], O_RDONLY);
	while(read(fd, &buffer, 1) > 0)
		buffer_len++;
	close(fd);
	return(buffer_len);
}

/*
char *mini_gnl(int fd, char **argv)
{
	int buffer_len;
	char *big_buffer;
	char *final_str;

	buffer_len = calculate_buffer_length(fd, argv);
	big_buffer = malloc(sizeof(char) * (buffer_len + 1));
	final_str = malloc(sizeof(char) * (buffer_len + 1));	
	if(big_buffer == NULL || final_str == NULL)
		return("mini_gnl memory allocation failed\n");
	fd = open(argv[1], O_RDONLY);
	read(fd, big_buffer, buffer_len);
	big_buffer[buffer_len] = '\0';
	ft_strcpy(final_str, big_buffer);
	free(big_buffer);
	close(fd);
	return(final_str);
}
*/

char *mini_gnl(int fd, char **argv)
{
	int buffer_len;
	char *big_buffer;

	buffer_len = calculate_buffer_length(fd, argv);
	big_buffer = malloc(sizeof(char) * (buffer_len + 1));
	if(big_buffer == NULL)
		return("mini_gnl memory allocation failed\n");
	fd = open(argv[1], O_RDONLY);
	read(fd, big_buffer, buffer_len);
	big_buffer[buffer_len] = '\0';
	close(fd);
	return(big_buffer);	
}

void ft_ssl_parsing(int fd, char **argv)
{
	char *full_str;

	error_messages(fd, argv);
	full_str = mini_gnl(fd, argv);
	printf("%s", full_str);
	free(full_str);
}

void handle_stdin(char **argv)
{
	char *str;
	while(1)
	{
		str = argv[1];
	}
	printf("%s", str);
}

int main(int argc, char *argv[])
{
	int fd;

	fd = open(argv[1], O_RDONLY);

//	if(argc == 1)
//		handle_stdin(argv);
	if(argc > 1)
		ft_ssl_parsing(fd, argv);
//	while(1);

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
