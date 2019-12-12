/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 20:05:11 by mbutt             #+#    #+#             */
/*   Updated: 2019/12/11 20:05:32 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	main(int argc, char *argv[])
{
	t_ssl	ssl;

	ft_bzero(&ssl, sizeof(t_ssl));
	if (argc == 1)
		handle_stdin(&ssl);
	else if (argc > 1)
		ft_ssl_parsing(argc, argv);
}
