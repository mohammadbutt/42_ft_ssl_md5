/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:02:34 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/13 19:07:01 by mbutt            ###   ########.fr       */
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
	ft_printf("ft_ssl: %s: %s\n", argv[1], strerror(errno));
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

/*
** Traverses through a file and counts the number of characters in the file.
** For example: will go through a file called alpha.txt, that has the following
** content:
** a
** bc
** def
** calculate_buffer_length will return 6.
*/

int calculate_buffer_length(int fd, char *argv)
{
	char buffer;
	int buffer_len;

	buffer_len = 0;
	fd = open(argv, O_RDONLY);
	while(read(fd, &buffer, 1) > 0)
		buffer_len++;
	close(fd);
	return(buffer_len);
}

/*
** Function mini_gnl reads a file and stores the content/text of that file to be
** used for hashing later.
*/


char *mini_gnl(int fd, char *argv)
{
	int buffer_len;
	char *big_buffer;

	buffer_len = calculate_buffer_length(fd, argv);
	big_buffer = malloc(sizeof(char) * (buffer_len + 1));
	if(big_buffer == NULL)
		return("mini_gnl memory allocation failed\n");
	fd = open(argv, O_RDONLY);
	read(fd, big_buffer, buffer_len);
	big_buffer[buffer_len] = '\0';
	close(fd);
	return(big_buffer);	
}


/*
char *mini_gnl(int fd, char *argv)
{
	char buffer[2];
	char *temp;
	char *new_string;

	new_string = malloc(sizeof(char) * (2));
	if(new_string == NULL)
		return("memory allocation failed in mini_gnl\n");
	new_string[0] = 0;
	fd = open(argv, O_RDONLY);
	while(read(fd, buffer, 1) > 0)
	{
		temp = new_string;
		new_string = ft_strjoin(temp, buffer);
		free(temp);
	}
	close(fd);
	return(new_string);
}
*/
char *mini_gnl_stdin(void)
{
	char buffer[2];
	char *temp;
	char *new_string;

	new_string = malloc(sizeof(char) * (2));
	if(new_string == NULL)
		return("memory allocation failed in mini_gnl_stdin.\n");
	new_string[0] = 0;
	while((read(0, buffer, 1)) > 0)
	{
//		printf("%d\n", return_of_read);
		temp = new_string;
		new_string = ft_strjoin(temp, buffer);
		free(temp);
	}
//	close(fd);
	return(new_string);
}


void ft_ssl_parsing(int fd, char **argv)
{
	char *full_str;

	error_messages(fd, argv);
	full_str = mini_gnl(fd, argv[1]);
	printf("%s", full_str);
	free(full_str);
}

void ft_print_usage(char *buffer)
{
	ft_printf("ft_ssl:Error: '%s' is an invalid command.\n\n", buffer);
	ft_printf("Message Digest Commands:\n");
	ft_printf("md5\nsha224\nsha256\nsha384\nsha512\n\n");
}


void read_stdin_loop(char *buffer)
{
	int return_of_read;

	return_of_read = 0;
	while(1)
	{
		ft_printf("ft_SSL> ");
		buffer[0] = 0;
		return_of_read = read(0, buffer, 8);
		if(return_of_read > 1)
		{
			buffer[return_of_read - 1] = '\0';
			if (ft_strcmp(buffer, "md5") == 0)
				break;
			else if (ft_strcmp(buffer, "sha224") == 0)
				break;
			else if (ft_strcmp(buffer, "sha256") == 0)
				break;
			else if (ft_strcmp(buffer, "sha384") == 0)
				break;
			else if (ft_strcmp(buffer, "sha512") == 0)
				break;
			else
				ft_print_usage(buffer);
		}
	}
}

void handle_stdin(void)
{
//	char *string;          ////////////////////////////
	char buffer[8];

	read_stdin_loop(buffer);
//	char *md_command;
	ft_printf("%s", buffer);
//	ft_printf("ft_SSL> ");
//	md_command = is_md_command_valid();
//	check_if // -1 -> strcmp != 0 and usage, 0i, 1
//	string = mini_gnl_stdin();

//	system(string);
//	if(ft_strcmp(string, "md5") == 0)
//		printf("%s", string); ///////////////////
//	free(string);       ///////////////
//	char buffer;

//	while(read(0, &buffer, 1) > 0)
//		ft_printf("%c", buffer);

//	str = mini_gnl(0, argv[1]);
	
//	printf("%s", str);
//	while(1)
//	{
//		str = argv[1];
//	}
//	printf("%s", str);
}

int main(int argc, char *argv[])
{
	int fd;

	fd = open(argv[1], O_RDONLY);

	if(argc == 1)
		handle_stdin();
	if(argc > 1)
		ft_ssl_parsing(fd, argv);
//	system("leaks ft_ssl");
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
