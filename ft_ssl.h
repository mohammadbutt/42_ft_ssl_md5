/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:37:36 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/27 22:30:47 by mbutt            ###   ########.fr       */
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
/*
** Structs----------------------------------------------------------------------
*/

/*
** g_md5_table_m hex values.
** 0 = 0x0, 1 = 0x1, 2 = 0x2, 3 = 0x3,
** 4 = 0x4, 5 = 0x5, 6 = 0x6, 7 = 0x7,
** 8 = 0x8, 9 = 0x9, 10 = 0xa, 11 = 0xb,
** 12 = 0xc, 13 = 0xd, 14 = 0xe, 15 = 0xf
** Also have a compute_md5_table_x
*/

static uint32_t g_md5_table_x[64] =
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

typedef struct	s_ssl_context
{
	uint32_t	state[4];
	uint32_t	count[2];
}				t_ssl_context;

/*
typedef struct s_md5
{
	char		
}
*/

typedef struct		s_ssl
{
	t_ssl_flag		flag;
	t_ssl_skip		skip;
	t_ssl_context	context;
//	bool		skip_if_to_collect_flags;
//	bool		skip_mini_gnl_stdin_for_flag_p;
//	int			count_of_flag_p;
	char		*message_digest_algo;
	char		*message_to_digest;
	char		*md5_padded_message;
}				t_ssl;


/*
** Function Prototypes----------------------------------------------------------
*/

#endif
