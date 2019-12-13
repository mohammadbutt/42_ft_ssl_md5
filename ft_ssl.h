/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:37:36 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/12 18:55:15 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "srcs/ft_printf/srcs/ft_printf.h"
# include "srcs/ft_printf/srcs/mini_libft/mini_libft.h"
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include <stdio.h>

/*
** Notes about headers that are included:
** #include <fcntl.h> 	to access open(2).
** #include <string.h>	to access strerror(3).
** #include <errno.h>	to access errno(3)
** #include <math.h>	to access sin(3).
*/

/*
** Macros-----------------------------------------------------------------------
*/

# define SSL_VALID_FLAG "pqrs"
# define FT_64_BIT_LENGTH 64
# define FT_64_BYTE 64
# define FT_512_BIT 64
# define FT_448_BIT 56
# define FT_64_BIT 8

/*
** Tables-----------------------------------------------------------------------
*/

/*
** Table from wiki:
** en.wikipedia.org/wiki/SHA-2#Pseudocode
*/

static uint32_t g_sha256_table_k[64] =
{
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

/*
** Table from wiki
** en.wikipedia.org/wiki/SHA-2#Pseudocode
*/
static uint64_t g_sha512_table_k[80] =
{
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f,
	0xe9b5dba58189dbbc, 0x3956c25bf348b538, 0x59f111f1b605d019,
	0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242,
	0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
	0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
	0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 0x2de92c6f592b0275,
	0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f,
	0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc,
	0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6,
	0x92722c851482353b, 0xa2bfe8a14cf10364, 0xa81a664bbc423001,
	0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
	0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99,
	0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
	0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc,
	0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915,
	0xc67178f2e372532b, 0xca273eceea26619c, 0xd186b8c721c0c207,
	0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba,
	0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
	0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
	0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

/*
** Structs----------------------------------------------------------------------
*/
/*
** Values a0, b0, c0, d0 and A, B, C, D are mapped based on wiki page of md5
**
** ssl->md5.a0 = a0 of wiki
** ssl->md5.b0 = b0 of wiki
** ssl->md5.c0 = c0 of wiki
** ssl->md5.d0 = d0 of wiki
**
** ssl->md5.a = A of wiki
** ssl->md5.b = B of wiki
** ssl->md5.c = C of wiki
** ssl->md5.d = D of wiki
**
** a0, b0, c0, d0 gets initialized first to below values based on wiki md5 page:
** a0 = 0x67452301
** b0 = 0xefcdab89
** c0 = 0x98badcfe
** d0 = 0x10325476
**
** a, b, c, d gets values from a0, b0, c0, d0
*/

/*
** padded_message can be char or uint8_t
*/

typedef struct	s_ssl_md5
{

	uint32_t	table_g[64];
	uint32_t	table_k[64];
	uint32_t	table_s[64];
	char		*padded_message;
	size_t		padded_message_len;
	uint32_t	a0;
	uint32_t	b0;
	uint32_t	c0;
	uint32_t	d0;
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
}				t_ssl_md5;

/*
** Values in struct t_ssl_sha256 follows the naming convention from wikipedia
**
** Note about ss0 and ss1;
** ss0 denotes capital S0 from wiki
** ss1 denotes capital S1 from wiki
**
** Norminette does not allow capital lettered variable names and I dont want to
** put S0 and S1 in macros.
*/

typedef struct	s_ssl_sha256
{
	uint32_t	table_w[64];
	uint32_t	*padded_message;
	uint32_t	padded_message_len;
	uint32_t	h0;
	uint32_t	h1;
	uint32_t	h2;
	uint32_t	h3;
	uint32_t	h4;
	uint32_t	h5;
	uint32_t	h6;
	uint32_t	h7;
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	e;
	uint32_t	f;
	uint32_t	g;
	uint32_t	h;
	uint32_t	s0;
	uint32_t	s1;
	uint32_t	ss0;
	uint32_t	ss1;
	uint32_t	ch;
	uint32_t	maj;
	uint32_t	temp1;
	uint32_t	temp2;
	uint32_t	chunk_of_512bit;

}				t_sha256;

typedef struct	s_ssl_sha512
{
	uint64_t	table_w[128];
	uint64_t	*padded_message;
	uint64_t	padded_message_len;
	uint64_t	h0;
	uint64_t	h1;
	uint64_t	h2;
	uint64_t	h3;
	uint64_t	h4;
	uint64_t	h5;
	uint64_t	h6;
	uint64_t	h7;
	uint64_t	a;
	uint64_t	b;
	uint64_t	c;
	uint64_t	d;
	uint64_t	e;
	uint64_t	f;
	uint64_t	g;
	uint64_t	h;
	uint64_t	s0;
	uint64_t	s1;
	uint64_t	ss0;
	uint64_t	ss1;
	uint64_t	ch;
	uint64_t	maj;
	uint64_t	temp1;
	uint64_t	temp2;
	uint64_t	number_of_512bit_chunk;
	uint64_t	chunk_of_1024bit;
}				t_sha512;

typedef struct	s_ssl_flag
{
	bool		p : 1;
	bool		s : 1;
	bool		q : 1;
	bool		r : 1;
	bool		ft_stdin : 1;
}				t_ssl_flag;

typedef struct	s_ssl_skip
{
	bool		if_to_collect_flags : 1;
	bool		mini_gnl_stdin_for_flag_p : 1;
}				t_ssl_skip;

typedef struct	s_ssl
{
	t_ssl_flag	flag;
	t_ssl_skip	skip;
	t_ssl_md5	md5;
	t_sha256	sha256;
	t_sha512	sha512;
	char		*message_digest_algo;
	char		*message_to_digest;
	char		*file_name;
}				t_ssl;

/*
** Function Prototypes----------------------------------------------------------
*/

/*
** ssl_parse_standard_input.c---------------------------------------------------
*/

char			*read_stdin_loop(char *message_digest_algorithm);
void			handle_stdin(t_ssl *ssl);
void			if_control_d_exit_program(int return_of_read);
bool			is_md_algorithm_valid(char *str);
bool			is_there_p_or_s(char *argv);

/*
** ssl_parse_pqrs.c-------------------------------------------------------------
*/

void			ft_ssl_parse_qr(int argc, char **argv);
void			ft_ssl_parse_pqrs_no_dash_adjust_flags(t_ssl *ssl);
void			ft_ssl_parse_pqrs_no_dash(char **argv, t_ssl *ssl, int i);
void			ft_ssl_parse_pqrs(int argc, char **argv);
void			ft_ssl_parsing(int argc, char **argv);

/*
** ssl_collect_flags.c----------------------------------------------------------
*/

bool			is_ssl_flag_valid(char c);
void			collect_ssl_flag(t_ssl *ssl, char c);
void			ft_ssl_collect_flags_process_p(t_ssl *ssl);
void			ft_ssl_collect_flags_process_s(char *message, t_ssl *ssl,int j,
				int argc);
void			ft_ssl_collect_flags(char *argv, t_ssl *ssl, int j, int argc);

/*
** ssl_get_next_line.c----------------------------------------------------------
*/

int				calculate_buffer_length(int fd, char *argv);
char			*mini_gnl(int fd, char *argv);
char			*mini_gnl_stdin(void);

/*
** ssl_error_messages.c---------------------------------------------------------
*/

void			error_invalid_file_permission(t_ssl *ssl, int fd, char *argv);
void			error_message_dir(t_ssl *ssl, int fd, char *argv);
bool			error_messages(t_ssl *ssl, int fd, char *argv);

/*
** ssl_usage_and_option.c-------------------------------------------------------
*/

void			ssl_exit_illegal_option(char c);
void			ft_option_requires_argument(char *digest_method);
void			ft_print_usage(char *buffer);

/*
** ssl_store_hash_free_message.c------------------------------------------------
*/

void			hash_message(t_ssl *ssl);
void			store_hash_free_message(t_ssl *ssl, char *message_to_digest);

/*
** ssl_hash_message_md5.c-------------------------------------------------------
*/

void			ft_md5_init(t_ssl *ssl);
void			ft_md5_padding(t_ssl *ssl);
void			ft_md5_transformation(t_ssl *ssl);
void			ft_md5_format_print(t_ssl *ssl);
void			hash_message_md5(t_ssl *ssl);

/*
** ssl_md5_table_g_k_s.c--------------------------------------------------------
*/

void			compute_md5_table_g(uint32_t *num);
void			compute_md5_table_k(uint32_t *num);
void			compute_md5_table_g_k_s(t_ssl *ssl);

/*
** ssl_md5_table_s.c------------------------------------------------------------
*/

void			compute_md5_table_s_0_to_31(uint32_t *num);
void			compute_md5_table_s_32_to_63(uint32_t *num);
void			compute_md5_table_s(uint32_t *num);

/*
** ssl_md5_print_and_helper.c---------------------------------------------------
*/

uint32_t		rotate_left_32bit(uint32_t value, uint32_t rotate_n_bits);
void			ft_md5_print(t_ssl *ssl, char character);

/*
** ssl_md5_core.c---------------------------------------------------------------
*/

uint32_t		md5_function_fghi(uint32_t j, uint32_t b, uint32_t c,
				uint32_t d);
void			ft_update_md5_abcd(t_ssl *ssl);
void			swap_md5_adc_with_dcb(t_ssl *ssl);
void			ft_add_md5_abcd_to_a0b0c0d0(t_ssl *ssl);
void			swap_bits_to_fix_endian(t_ssl *ssl);

/*
** ssl_hash_message_sha256.c----------------------------------------------------
*/

void			ft_sha256_init(t_ssl *ssl);
void			ft_sha256_padding(t_ssl *ssl);
void			ft_sha256_transformation(t_ssl *ssl);
void			hash_message_sha256(t_ssl *ssl);

/*
** ssl_sha256_core.c------------------------------------------------------------
*/

void			ft_update_sha256_abcdefgh(t_ssl *ssl);
void			ft_add_sha256_abcdefgh_to_h_values(t_ssl *ssl);
void			ft_sha256_swap_abcdefgh(t_ssl *ssl);
void			ft_sha256_process_512bit_chunk(t_ssl *ssl, uint32_t chunk);
void			ft_sha256_compression(t_ssl *ssl);

/*
** ssl_sha256_helper.c----------------------------------------------------------
*/

uint32_t		rotate_right_32bit(uint32_t value, uint32_t rotate_n_bits);
uint32_t		shift_right_32bit(uint32_t value, uint32_t shift_n_bits);
uint32_t		ft_swap_32bit(uint32_t value);
void			ft_bzero_num_array_32bit(uint32_t *num, uint32_t size);
uint32_t		calculate_ssl_padding_32bit(uint32_t padding);

/*
** ssl_sha256_print.c----------------------------------------------------------
*/

void			ft_sha256_print(t_ssl *ssl, char c);
void			ft_sha256_format_print(t_ssl *ssl, char *algo_name);

/*
** ssl_hash_message_sha224.c----------------------------------------------------
*/

void			ft_sha224_init(t_ssl *ssl);
void			hash_message_sha224(t_ssl *ssl);

/*
** ssl_hash_message_sha512.c----------------------------------------------------
*/

void			ft_sha512_init(t_ssl *ssl);
void			ft_sha512_padding(t_ssl *ssl);
void			ft_sha512_transformation(t_ssl *ssl);
void			hash_message_sha512(t_ssl *ssl);

/*
** ssl_sha512_core.c
*/

void			ft_update_sha512_abcdefgh(t_ssl *ssl);
void			ft_add_sha512_abcdefgh_to_h_values(t_ssl *ssl);
void			ft_sha512_swap_abcdefgh(t_ssl *ssl);
void			ft_sha512_process_1024bit_chunk(t_ssl *ssl, uint64_t chunk);
void			ft_sha512_compression(t_ssl *ssl);

/*
** ssl_sha256_helper.c----------------------------------------------------------
*/

uint64_t		rotate_right_64bit(uint64_t value, uint64_t rotate_n_bits);
uint64_t		shift_right_64bit(uint64_t value, uint64_t shift_n_bits);
uint64_t		ft_swap_64bit(uint64_t value);
void			ft_bzero_num_array_64bit(uint64_t *num, uint64_t size);
uint64_t		calculate_ssl_padding_64bit(uint64_t padding);

/*
** ssl_sha512_print.c-----------------------------------------------------------
*/

void			ft_sha512_print(t_ssl *ssl, char c);
void			ft_sha512_format_print(t_ssl *ssl, char *algo_name);



uint64_t shift_right_64bit(uint64_t value, uint64_t rotate_by);
uint64_t rotate_right_64bit(uint64_t value, uint64_t rotate_by);
void       ft_bzero_num_array_64bit(uint64_t *num, uint64_t n);
void                 ft_sha512_compression(t_ssl *ssl);
void                 ft_sha512_print(t_ssl *ssl, char c);
void	                ft_sha512_format_print(t_ssl *ssl, char *str);
uint64_t ft_swap_64bit(uint64_t value);
void    ft_sha512_process_1024bit_chunk(t_ssl *ssl, uint64_t chunk);
uint64_t		calculate_ssl_padding_64bit(uint64_t padding);
void       ft_bzero_num_array_32bit(uint32_t *num, uint32_t n);
uint32_t rotate_right_32bit(uint32_t value, uint32_t rotate_by);
uint32_t shift_right_32bit(uint32_t value, uint32_t rotate_by);

void    ft_sha256_process_512bit_chunk(t_ssl *ssl, uint32_t chunk);
void                 ft_sha256_compression(t_ssl *ssl);
void    ft_sha224_init(t_ssl *ssl);
void    ft_sha256_print(t_ssl *ssl, char c);
void    ft_sha256_format_print(t_ssl *ssl, char *str);
void    zero_four_variables(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d);
uint32_t ft_swap_32bit(uint32_t value);
double  ft_fabs(double num);
uint64_t ft_pow(int base, int exponent);
void    compute_md5_table_s(uint32_t *num);
void    ft_add_md5_abcd_to_a0b0c0d0(t_ssl *ssl);
uint32_t calculate_ssl_padding_32bit(uint32_t padding);
void zero_three_variables(uint32_t *a, uint32_t *b, uint32_t *c);
void compute_md5_table_g_k_s(t_ssl *ssl);
void ft_update_md5_abcd(t_ssl *ssl);
uint32_t md5_function_fghi(uint32_t i, uint32_t b, uint32_t c, uint32_t d);
void swap_md5_adc_with_dcb(t_ssl *ssl);
uint32_t rotate_left_32bit(uint32_t a, uint32_t b);
void ft_md5_print(t_ssl *ssl, char c);
void swap_bits_to_fix_endian(t_ssl *ssl);
void hash_message_md5(t_ssl *ssl);
void hash_message_sha224(t_ssl *ssl);
void hash_message_sha256(t_ssl *ssl);
void hash_message_sha384(t_ssl *ssl);
void hash_message_sha512(t_ssl *ssl);
void ft_option_requires_argument(char *digest_method);
void ssl_exit_illegal_option(char c);
void ft_initialize_ssl_flag(t_ssl *ssl);
bool error_messages(t_ssl *ssl, int fd, char *argv);
void ft_ssl_collect_flags(char *argv, t_ssl *ssl, int j, int argc);
void handle_stdin(t_ssl *ssl);
void ft_print_usage(char *buffer);
void store_hash_free_message(t_ssl *ssl, char *message_to_digest);

/*
** Forbidden function macros----------------------------------------------------
** To ensure forbidden function was not used
*/

/*
**# define FORBIDDEN(func) sorry_##func##_is_a_forbidden_function
**
**# undef strcpy
**# define strcpy(x,y) FORBIDDEN(strcpy)
**# undef strcat
**# define strcat(x,y) FORBIDDEN(strcat)
**# undef strncpy
**# define strncpy(x,y,n) FORBIDDEN(strncpy)
**# undef strncat
**# define strncat(x,y,n) FORBIDDEN(strncat)
**# undef bzero
**# define bzero(s, n) FORBIDDEN(strcpy)
**
**# undef sprintf
**# undef vsprintf
**# undef printf
**# ifdef HAVE_VARIADIC_MACROS
**# define sprintf(...) FORBIDDEN(sprintf)
**# define vsprintf(...) FORBIDDEN(vsprintf)
**# define printf(...) FORBIDDEN(printf)
**# else
**# define sprintf(buf,fmt,arg) FORBIDDEN(sprintf)
**# define vsprintf(buf,fmt,arg) FORBIDDEN(sprintf)
**# define printf(fmt, arg) FORBIDDEN(printf)
**# endif
*/

#endif
