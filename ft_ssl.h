/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:37:36 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/10 16:06:03 by mbutt            ###   ########.fr       */
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
# define FT_64_BIT 8

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
** Will not use g_md5_table_g[64], but might keep it for reference only
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

typedef struct	s_ssl_flag
{	
//	int			count_of_p;
	bool		p : 1;
	bool		s : 1;
	bool		q : 1;
	bool		r : 1;
//	bool		file_name : 1;
	bool		ft_stdin : 1;
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
	uint32_t	*padded_message; // malloc
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
//	uint32_t	number_of_512bit_chunk;
	uint32_t	chunk_of_512bit;

}				t_ssl_sha256;


typedef struct s_ssl_sha512
{
//	uint64_t	table_k[80]; Have global table
	uint64_t	table_w[80];
	uint64_t	*padded_message; // malloc
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
}				t_ssl_sha512;


typedef struct		s_ssl
{
	t_ssl_flag		flag;
	t_ssl_skip		skip;
	t_ssl_md5		md5;
	t_ssl_sha256	sha256;
	t_ssl_sha512	sha512;
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
