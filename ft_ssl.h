/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:37:36 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/04 12:33:54 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

#include "srcs/ft_printf/srcs/ft_printf.h"
#include "srcs/ft_printf/srcs/mini_libft/mini_libft.h"
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#include <stdio.h>
/*
** Notes about headers that are included:
** #include <fcntl.h> 	to access open(2).
** #include <string.h>	to access strerror(3).
** #include <errno.h>	to access errno(3)
** #include <math.h>	to access sin(3).
*/

/*
*** These Macros will be deleted later. Just for testing
*/

# define NL_HASH "d41d8cd98f00b204e9800998ecf8427e"
# define AB_NL_HASH "daa8075d6ac5ff8d0c6d4650adb4ef29"
# define AB_HASH "187ef4436122d1cc2f40dc2b92f0eba0"


/*
** Macros-----------------------------------------------------------------------
*/

# define SSL_VALID_FLAG "pqrs"
# define FT_64_BIT_LENGTH 64
# define FT_64_BYTE 64
/*
** Structs----------------------------------------------------------------------
*/

/*
** g_md5_table_m hex values.
** 0 = 0x0, 1 = 0x1, 2 = 0x2, 3 = 0x3,
** 4 = 0x4, 5 = 0x5, 6 = 0x6, 7 = 0x7,
** 8 = 0x8, 9 = 0x9, 10 = 0xa, 11 = 0xb,
** 12 = 0xc, 13 = 0xd, 14 = 0xe, 15 = 0xf
** Also have a compute_md5_table_g
**
** Will not use g_md5_table_g[64], but might keep it fo reference
*/

static uint32_t g_md5_table_g[64] =
{
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12,
	5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2,
	0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9
};

typedef struct	s_ssl_flag
{	
//	int			count_of_p;
	bool		p : 1;
	bool		s : 1;
	bool		q : 1;
	bool		r : 1;
}				t_ssl_flag;

typedef struct	s_ssl_skip
{
	bool		if_to_collect_flags : 1;
	bool		mini_gnl_stdin_for_flag_p : 1;
}				t_ssl_skip;

/*
typedef struct	s_ssl_context
{
	uint32_t	state[4];
	uint32_t	count[2];
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
}				t_ssl_context;
*/

/*
typedef struct	s_ssl_state
{
	uint32_t	a0;
	uint32_t	b0;
	uint32_t	c0;
	uint32_t	d0;
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
}				t_ssl_state;
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

typedef struct s_ssl_md5
{

	uint32_t	table_g[64];
	uint32_t	table_k[64];
	uint32_t	table_s[64];
	char		*padded_message; // malloced
	size_t		padded_message_len; // should this be size_t?
	uint32_t	a0;
	uint32_t	b0;
	uint32_t	c0;
	uint32_t	d0;
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
}				t_ssl_md5;


typedef struct		s_ssl
{
	t_ssl_flag		flag;
	t_ssl_skip		skip;
	t_ssl_md5		md5;
	char			*message_digest_algo;
	char			*message_to_digest;
	char			*file_name;

//	t_ssl_state		state;
//	t_ssl_context	context;
//	bool		skip_if_to_collect_flags;
//	bool		skip_mini_gnl_stdin_for_flag_p;
//	int			count_of_flag_p;
//	char		*md5_padded_message; // malloced
//	uint32_t	md5_padded_message_len;
//	uint32_t	md5_table
}				t_ssl;


/*
** Function Prototypes----------------------------------------------------------
*/

#endif
