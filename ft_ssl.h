/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:37:36 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/25 21:59:06 by mbutt            ###   ########.fr       */
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

/*
** Structs----------------------------------------------------------------------
*/

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
}				t_ssl;


/*
** Function Prototypes----------------------------------------------------------
*/

#endif
