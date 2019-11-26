/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:18:06 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/25 19:11:50 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** Adding md5 functions
*/

/*
** Add the below functions in math.c file
*/

uint64_t ft_pow(int base, int exponent)
{
	uint64_t	total;
	int			i;

	total = base;
	i = 1;
	while(i < exponent)
	{
		total = total * base;
		i++;
	}
	return(total);
}

/*
** ft_fabs is used to convert negative floating point values into positive.
**
** Note: Has to be double, data type cannot be float because absolute value will
** be different if the data type is float instead of double.
*/

double ft_fabs(double num)
{
	if(num < 0)
		num = -1 * num;
	return(num);
}


//void compute_md5_table_s_0_to_31(unsigned int *num)
void compute_md5_table_s_0_to_31(uint32_t *num)
{
	int i;

	i = 0;
	while(i >= 0 && i <= 15)
	{
		num[i++] = 7;
		num[i++] = 12;
		num[i++] = 17;
		num[i++] = 22;
	}
	while(i >= 16 && i <= 31)
	{
		num[i++] = 5;
		num[i++] = 9;
		num[i++] = 14;
		num[i++] = 20;
	}
}

//void compute_md5_table_s_32_to_63(unsigned int *num)
void compute_md5_table_s_32_to_63(uint32_t *num)
{
	int i;

	i = 32;
	while (i >= 32 && i <= 47)
	{
		num[i++] = 4;
		num[i++] = 11;
		num[i++] = 16;
		num[i++] = 23;
	}
	while (i >= 48 && i <= 63)
	{
		num[i++] = 6;
		num[i++] = 10;
		num[i++] = 15;
		num[i++] = 21;
	}
}
/*
** s specifies the pre round shift amount
*/
//void compute_md5_table_s(unsigned int *num)
void compute_md5_table_s(uint32_t *num)
{
	ft_bzero(num, sizeof(num));
	compute_md5_table_s_0_to_31(num);
	compute_md5_table_s_32_to_63(num);
}

//void compute_md5_table_k(unsigned int *num)
void compute_md5_table_k(uint32_t *num)
{
	uint32_t i;
	int base;
	int exponent;

	i = 0;
	base = 2;
	exponent = 32;
	ft_bzero(num, sizeof(num));
	while(i < 64)
	{
		num[i] = (uint32_t)(ft_pow(base, exponent) * ft_fabs(sin(i + 1)));
		i++;
	}
		
}
/*
** print_error_messages takes a 2d array and if the file descriptor is -1, then
** the error message is printed.
** File desciptor will be -1 under 1 of 2 conditions:
** 1. A file path is an invalid file path. "No such file or directory"
** 2. A file has permission denied access. "Permission denied"
*/

void error_invalid_file_permission(int fd, char *argv)
{
	ft_printf("ft_ssl: %s: %s\n", argv, strerror(errno));
//	fd = fd * 1;
	close(fd);
//	exit(EXIT_SUCCESS);
}

void test_md5_table_k(void)
{
	uint32_t num[64];
	uint32_t i;

	i = 0;
//	ft_bzero(num, sizeof(num));
	compute_md5_table_k(num);
	while(i < 64)
	{
		if(((i) % 4) == 0)
			printf("{ ");
		printf("%#x, ", num[i]);
		if(((i + 1) % 4) == 0)
			printf("}\n\n");
		i++;
	}

}

void test_md5_table_s(void)
{
	uint32_t num[64];
	uint32_t i;

	i = 0;
	compute_md5_table_s(num);
	while(i < 64)
	{
		if(i == 0 || i == 16 || i == 32 || i == 48)
			printf("{ ");
		printf("%u, ", num[i]);
		if(i == 15 || i == 31 || i == 47 || i == 63)
			printf("}\n\n");
		i++;
	}

}

void hash_message(t_ssl *ssl)//, char *message_digest_algo, char *message_to_digest)
{
//	ssl->flag.p = ssl->flag.p;
//	unsigned int num[64];
//	int i = 0;

	ft_printf("message digest algo: |%s|\n", ssl->message_digest_algo);
	ft_printf("message to digest: |%s|\n", ssl->message_to_digest);
	test_md5_table_k();
	test_md5_table_s();

//	compute_md5_table(num);
//	printf("{ ");
//	while(i < 64)
//	{
//		if(((i) % 4) == 0)
//			printf("{ ");
//		printf("%#x, ", num[i]);
//		if(((i + 1) % 4) == 0)
//			printf("}\n\n");
//		if((i + 1) % 4 == 0)
//			printf("\n");
//		i++;
//	}
}

/*
** print_error_message_dir prints error message for the directory
** If a file path is a directory it will still have a valid file descriptor of
** 1, but when the directory is opened with read, the return value of read will
** be -1 if it is a directory. strerror and errno are used the print the error
** message. "Is a directory"
*/

void error_message_dir(int fd, char *argv)
{
	ft_printf("ft_ssl: %s: %s\n", argv, strerror(errno));
//	fd = fd * 1;
	close(fd);
//	exit(EXIT_SUCCESS);
}

/*
** error messages calls onto eror_invalid_file_permission and
** error_message_dir functions.
** At the end closes the file descriptor
*/

bool error_messages(int fd, char *argv)
{
	char temp_buff[2];
	ssize_t return_of_read;

	return_of_read = 0;
	if(fd == -1)
	{
		error_invalid_file_permission(fd, argv);
		return(true);
	}
	return_of_read = read(fd, temp_buff, 1);
	if(return_of_read == -1)
	{
		error_message_dir(fd, argv);
		return(true);
	}
	close(fd);
	return(false);
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


char *mini_gnl_stdin(void)
{
	char buffer[2];
	char *temp;
	char *new_string;
	int i;
	
	i = 1;
	new_string = malloc(sizeof(char) * (2));
	if(new_string == NULL)
		return("memory allocation failed in mini_gnl_stdin.\n");
	new_string[0] = 0;
	while((read(0, buffer, 1)) > 0)
	{
		buffer[i] = '\0';
		temp = new_string;
		new_string = ft_strjoin(temp, buffer);
		free(temp);
	}
	return(new_string);
}

bool is_ssl_flag_valid(char c)
{
	int i;

	i = 0;
	while(SSL_VALID_FLAG[i])
	{
		if(SSL_VALID_FLAG[i] == c)
			return(true);
		i++;
	}
	return(false);
}

void collect_ssl_flag(t_ssl *ssl, char c)
{
	if(c == 'p')
	{
		ssl->flag.p = true;
//		ssl->flag.count_of_p++;
	}
	else if(c == 'q')
		ssl->flag.q = true;
	else if(c == 'r')
		ssl->flag.r = true;
	else if(c == 's')
		ssl->flag.s = true;
}

/*
** ssl_exit_illegal_option is used when the flag is not one of the valid flag
** options -p, -q, -r, or -s.
*/

void ssl_exit_illegal_option(char c)
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

void ft_option_requires_argument(char *digest_method)
{
	ft_printf("%s: option requires an argument -- s\n", digest_method);
	ft_printf("usage: %s [-pqr] [-s string] [files ...]\n", digest_method);
//		free(digest_method);
	exit(EXIT_SUCCESS);
}
/*
void store_message_to_digest_for_s(char *argv, t_ssl *ssl)
{
	char *message_to_digest;
	int len_of_message;

	len_of_message = ft_strlen(argv);
	message_to_digest = malloc(sizeof(char) * (len_of_message + 1));
	ft_strcpy(message_to_digest, argv);
	ft_printf("%s", message_to_digest);
	free(message_to_digest);
	ssl->flag.s = ssl->flag.s; // Just a filler for -Wall -Wextra -Werror
}
*/

void store_hash_free_message(t_ssl *ssl, char *message_to_digest)
{
	ssl->message_to_digest = message_to_digest;
	hash_message(ssl);
	free(message_to_digest);
}

void ft_ssl_collect_flags_process_p(t_ssl *ssl)
{
	char *stdin_message_to_digest;
	char *empty_message_to_digest;

	if(ssl->skip.mini_gnl_stdin_for_flag_p == false)
	{
		stdin_message_to_digest = mini_gnl_stdin();
		store_hash_free_message(ssl, stdin_message_to_digest);
//		ssl->message_to_digest = stdin_message_to_digest;
//		hash_message(ssl);//, ssl->message_digest_algo, stdin_message_to_digest);
//		free(stdin_message_to_digest);
//		ssl->flag.count_of_p--;
		ssl->skip.mini_gnl_stdin_for_flag_p = true;
	}
	else if(ssl->skip.mini_gnl_stdin_for_flag_p == true)
	{
		empty_message_to_digest = malloc(sizeof(char) * (1));
		ft_strcpy(empty_message_to_digest, "");
		store_hash_free_message(ssl, empty_message_to_digest);
//		ssl->message_to_digest = empty_message_to_digest;
//		while(ssl->flag.count_of_p)
//		{
//			hash_message(ssl);
//			ssl->flag.count_of_p--;
//		}
//		free(empty_message_to_digest);
	}
}

void ft_ssl_collect_flags_process_s(char *message, t_ssl *ssl, int j, int argc)
{
	char *message_to_digest;

	if(ssl->flag.s == true && message[0] != '\0')
	{
		message_to_digest = malloc(sizeof(char) * (ft_strlen(message) + 1));
		ft_strcpy(message_to_digest, message);
		store_hash_free_message(ssl, message_to_digest);
//		ssl->message_to_digest = message_to_digest;
//		hash_message(ssl);//, ssl->message_digest_algo, message);
//		free(message_to_digest);
		ssl->flag.s = false;
	}
	else if(ssl->flag.s == true && j + 1 == argc)
		ft_option_requires_argument(ssl->message_digest_algo);
}


void ft_ssl_collect_flags(char *argv, t_ssl *ssl, int j, int argc)
{
	int i;
//	char *stdin_message_to_digest;

	i = 1;
	while(argv[i])
	{
		if(is_ssl_flag_valid(argv[i]) == true)
		{
			collect_ssl_flag(ssl, argv[i]);
			if (ssl->flag.p == true)
				ft_ssl_collect_flags_process_p(ssl);
			if(ssl->flag.s == true)
				break;
		}
		else if(is_ssl_flag_valid(argv[i]) == false)
			ssl_exit_illegal_option(argv[i]);
		i++;
	}
//	if (ssl->flag.p == true)
//		ft_ssl_collect_flags_process_p(ssl);
	ft_ssl_collect_flags_process_s(argv + i + 1, ssl, j, argc);
/*
	if(ssl->flag.p == true)
	{
		if(ssl->skip.mini_gnl_stdin_for_flag_p == false)
		{
			stdin_message_to_digest = mini_gnl_stdin();
			hash_message(ssl->message_digest_algo, stdin_message_to_digest);
			free(stdin_message_to_digest);
			ssl->flag.count_of_p--;
			ssl->skip.mini_gnl_stdin_for_flag_p = true;
		}
		while(ssl->flag.count_of_p)
		{
			hash_message(ssl->message_digest_algo, "");
			ssl->flag.count_of_p--;
		}
	}
	if(ssl->flag.s == true && argv[i + 1] != '\0')
	{
		hash_message(ssl->message_digest_algo, argv + i + 1);
		ssl->flag.s = false;
	}
	else if(ssl->flag.s == true && j + 1 == argc)
		ft_option_requires_argument(ssl->message_digest_algo);
*/
}

/*
** Function is_there_p_or_s is used in function ft_ssl_parse_qr.
** Because ft_ssl_parse_qr is supposed to only pint and hash a string if
** q or r are true, and both p and s are false. Since functions ft_ssl_parse_qr
** and ft_ssl_parse_pqrs both rely on ft_ssl_collect_flags to collect flags, it
** is helpful to have is_there_p_or_s, so if 'p' or 's' are true then the pogram
** leaves ft_ssl_parse_qr to go to ft_ssl_parse_pqrs.
**
** Return Value: returns true if there is 'p' or 's'.
** Returns false if there is no 'p' or 's'
*/
bool is_there_p_or_s(char *argv)
{
	int i;

	i = 1;
	while(argv[i])
	{
		if(argv[i] == 'p' || argv[i] == 's')
			return(true);
		i++;
	}
	return(false);
}
bool is_md_algorithm_valid(char *str)
{
	if (ft_strcmp(str, "md5") == 0 || ft_strcmp(str, "sha224") == 0)
		return(true);
	else if (ft_strcmp(str, "sha256") == 0 || ft_strcmp(str, "sha384") == 0)
		return(true);
	else if (ft_strcmp(str, "sha512") == 0)
		return(true);
	return(false);
}

/*
** flag.p and flag.s are set equal to -1 because if -s or -p never appear in
** any of the arguments, but -q or -r are present then the program should be
** able to enter the standard input/stdin mode to read from stream.
*/
void ft_print_usage(char *buffer)
{
	ft_printf("ft_ssl:Error: '%s' is an invalid command.\n\n", buffer);
	ft_printf("Message Digest Commands:\n");
	ft_printf("md5\nsha224\nsha256\nsha384\nsha512\n\n");
}

void ft_initialize_ssl_flag(t_ssl *ssl)
{	
	ft_bzero(&ssl->flag, sizeof(ssl->flag));
	ft_bzero(&ssl->skip, sizeof(ssl->skip));
//	ssl->flag.count_of_p = 0;

//	ssl->skip_if = false;
//	ssl->skip_if_to_collect_flags = false;
//	ssl->skip_p_stdin = false;
//	ssl->skip_mini_gnl_stdin_for_flag_p = false;
//	ssl->flag.p_count = 0;
//	ssl->count_of_flag_p = 0;
//	ssl->skip_p = false;
//	ssl->flag.p = -1;
//	ssl->flag.s = -1;
//	ssl->flag.q = false;
//	ssl->flag.r = false;
}

void ft_ssl_parse_qr(int argc, char **argv)
{
	t_ssl ssl;
	char *message_to_digest;
	int i;

	i = 2;
	ft_initialize_ssl_flag(&ssl);
	ssl.message_digest_algo = argv[1];
	while(i < argc)
	{
		if(is_there_p_or_s(argv[i]) == true)
			return;
		if(argv[i][0] == '-' && argv[i][1] != '\0')
			ft_ssl_collect_flags(argv[i], &ssl, i, argc);
		else
			return;
		i++;
	}
	message_to_digest = mini_gnl_stdin();
	store_hash_free_message(&ssl, message_to_digest);
//	ssl.message_to_digest = message_to_digest;
//	hash_message(&ssl);//, ssl.message_digest_algo, message_to_digest);
//	free(message_to_digest);
	exit(EXIT_SUCCESS);
}


void ft_ssl_parse_pqrs_no_dash_adjust_flags(t_ssl *ssl)
{
	if(ssl->flag.s == false && ssl->flag.p == false)
		ssl->skip.if_to_collect_flags = true;
	ssl->flag.s = false;
	ssl->flag.p = false;
//	ssl->flag.count_of_p = 0;
}

void ft_ssl_parse_pqrs_no_dash(char **argv, t_ssl *ssl, int i)
{
	char *message_to_digest;
	int fd;

	if(ssl->flag.s == true)
	{
		message_to_digest = malloc(sizeof(ft_strlen(argv[i]) + 1));
		ft_strcpy(message_to_digest, argv[i]);
		store_hash_free_message(ssl, message_to_digest);
//		ssl->message_to_digest = message_to_digest;
//		hash_message(ssl);//, ssl->message_digest_algo, argv[i]);
//		free(message_to_digest);
	}
	else if(ssl->flag.s == false)
	{
		fd = open(argv[i], O_RDONLY);
		if(error_messages(fd, argv[i]) == false)
		{
			message_to_digest = mini_gnl(fd, argv[i]);
			store_hash_free_message(ssl, message_to_digest);
//			ssl->message_to_digest = message_to_digest;
//			hash_message(ssl);//, ssl->message_digest_algo, message_to_digest);
//			free(message_to_digest);
		}
		(fd) && (close(fd));
	}
	ft_ssl_parse_pqrs_no_dash_adjust_flags(ssl);
//	if(ssl->flag.s == false && ssl->flag.p == false)
//		ssl->skip.if_to_collect_flags = true;
//	ssl->flag.s = false;
//	ssl->flag.p = false;
//	ssl->flag.count_of_p = 0;
}

/*
** ssl.skip_if is false as long as 's' or 'p' flag appear.
** If in an argument 's' or 'p' flag dont appear than ssl.skip_if is enabled and
** set to true, so flags are no more collected.
*/
void ft_ssl_parse_pqrs(int argc, char **argv)
{
	t_ssl ssl;
	int i;

	i = 2;
	ft_initialize_ssl_flag(&ssl);
	ssl.message_digest_algo = argv[1];
	while(i < argc)
	{
		if(argv[i][0] == '-' && argv[i][1] != '\0' && ssl.flag.s == false)
		{
			if(ssl.skip.if_to_collect_flags == false)	
				ft_ssl_collect_flags(argv[i], &ssl, i, argc);
		}
		else
			ft_ssl_parse_pqrs_no_dash(argv, &ssl, i);
		i++;
	}
}

void ft_ssl_parsing(int argc, char **argv)
{
	t_ssl ssl;
	char *message_to_digest;

	if(is_md_algorithm_valid(argv[1]) == false)
	{
		ft_print_usage(argv[1]);
		exit(EXIT_SUCCESS);
	}
	else if(is_md_algorithm_valid(argv[1]) == true && argc == 2)
	{
		message_to_digest = mini_gnl_stdin();
		ssl.message_digest_algo = argv[1];
		store_hash_free_message(&ssl, message_to_digest);
//		ssl.message_to_digest = message_to_digest;
//		hash_message(&ssl);//, argv[1], message_to_digest);
//		free(message_to_digest);
	}
	else
	{
		ft_ssl_parse_qr(argc, argv);
		ft_ssl_parse_pqrs(argc, argv);
	}
/*
	t_ssl ssl;
	char *full_str;
	int i;
	int fd;

	i = 1;
	ft_initialize_ssl_flag(&ssl);
	ft_printf("|%d|\n", argc);
//	ft_ssl_parsing_for_qr(argc, argv);
	while(i < argc)
	{
		fd = open(argv[i], O_RDONLY);
		if(argv[i][0] == '-' && argv[i][1] != '\0')
		{
			ft_ssl_collect_flags(argv[i], &ssl);
		}
		else if(error_messages(fd, argv[i]) == false)
		{
			full_str = mini_gnl(fd, argv[i]);
			printf("ft_ssl (%s) = ",argv[i]);
			free(full_str);
		}	
		(fd) && (close(fd));
		i++;
	}
*/
}


/*
** Since the program should be able to exit out any time Ctrl + D is pressed,
** this function is created to check if the return of read is equal to 0.
** If enter is pressed, return_of_read is equal to 1.
** But if Ctrl+D is pressed, return_of_read is equal to 0. which will exit the
** program, just like how the original openssl does.
*/

void if_control_d_exit_program(int return_of_read)
{
	if(return_of_read == 0)
		exit(EXIT_SUCCESS);
}

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

char *read_stdin_loop(char *message_digest_algorithm)
{
	int return_of_read;

	return_of_read = 0;
	while(1)
	{	
		ft_printf("ft_SSL> ");
		message_digest_algorithm[0] = 0;
		return_of_read = read(0, message_digest_algorithm, 8);
		if(return_of_read > 1)
		{
			message_digest_algorithm[return_of_read - 1] = '\0';
			if(is_md_algorithm_valid(message_digest_algorithm) == true)
			{
				return(message_digest_algorithm);
//				break;
			}
			else
				ft_print_usage(message_digest_algorithm);
		}
		if_control_d_exit_program(return_of_read);
//		if(return_of_read == 0)
//			exit(EXIT_SUCCESS);
	}
}

//void handle_stdin(void)
void handle_stdin(t_ssl *ssl)
{
	char message_digest_algo[8];
	char *message_to_digest;

	read_stdin_loop(message_digest_algo);
	message_to_digest = mini_gnl_stdin();
	ssl->message_digest_algo = message_digest_algo;
	store_hash_free_message(ssl, message_to_digest);
//	ssl->message_to_digest = message_to_digest;
//	hash_message(ssl);//message_digest_algo, message_to_digest);
//	free(message_to_digest);

//	char *md_command;
//	ft_printf("%s", message_digest_buffer);
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
	t_ssl ssl;
//	int fd;

//	fd = open(argv[1], O_RDONLY);

	if(argc == 1)
		handle_stdin(&ssl);
	else if(argc > 1)
		ft_ssl_parsing(argc, argv);
	
//	while(1);
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
