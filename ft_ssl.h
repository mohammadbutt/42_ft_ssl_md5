/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:37:36 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/05 21:52:04 by mbutt            ###   ########.fr       */
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
# define FT_512_BIT 64
# define FT_448_BIT 56

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
//	uint32_t	table_k[64]; Have global table
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

}				t_ssl_sha256;

typedef struct		s_ssl
{
	t_ssl_flag		flag;
	t_ssl_skip		skip;
	t_ssl_md5		md5;
	t_ssl_sha256	sha256;
	char			*message_digest_algo;
	char			*message_to_digest;
//	int				message_to_digest_len;
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
