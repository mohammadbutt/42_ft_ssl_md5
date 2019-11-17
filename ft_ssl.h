/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:37:36 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/13 23:09:07 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

#include "srcs/ft_printf/srcs/ft_printf.h"
#include "srcs/ft_printf/srcs/mini_libft/mini_libft.h"
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include <stdio.h>
/*
** Notes about headers that are included:
** #include <fcntl.h> 	to access open(2).
** #include <string.h>	to access strerror(3).
## #include <errno.h>	to access errno(3)
*/

/*
** Macros-----------------------------------------------------------------------
*/

# define SSL_VALID_FLAG "pqrs"


/*
** Structs----------------------------------------------------------------------
*/

typedef struct	s_ssl_flag
{
	bool		p : 1;
	bool		q : 1;
	bool		r : 1;
	bool		s : 1;
}				t_ssl_flag;

typedef struct	s_ssl
{
	t_ssl_flag	flag;
}				t_ssl;


/*
** Function Prototypes----------------------------------------------------------
*/

#endif
