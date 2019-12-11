# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbutt <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/11 14:35:05 by mbutt             #+#    #+#              #
#    Updated: 2019/12/10 15:07:34 by mbutt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NC:=\033[0m
GREEN:=\033[1;32m
ORANGE:=\033[0;33m
YELLOW:=\033[1;33m
CYAN:=\033[1;36m

NAME = ft_ssl
CC = gcc
CFLAGS = -I. -c -g
WFLAGS = -Wall -Wextra -Werror
DEBUG = -fsanitize=address -g #-ggdb
#DEBUG = -fsanitize=undefined # Cannot be used for md5, sha256, and so on...

SRC = *.c
OBJ = *.o

FT_PRINTF_DIR = srcs/ft_printf/
FT_PRINTF_STATIC = srcs/ft_printf/libftprintf.a

all: $(NAME)

$(NAME):
	@make -C $(FT_PRINTF_DIR) # runs Makefile for ft_printf
	@echo "${CYAN}Compiling Makefile for ft_ssl...⌛${NC}"
	@$(CC) $(CFLAGS) $(WFLAGS) $(SRC) # Creates object files
	@$(CC) $(OBJ) $(FT_PRINTF_STATIC) $(DEBUG) -o $(NAME)
	@echo "${GREEN}Generated ft_ssl successfully ✓.${NC}"

clean:
	make clean -C srcs/ft_printf/
	/bin/rm -rf $(OBJ)
	@echo "${ORANGE}Removed object files for ft_ssl ♻ .${NC}"

fclean:
	make fclean -C srcs/ft_printf/
	/bin/rm -rf $(NAME) $(OBJ)
	@echo "${ORANGE}Removed object files for ft_ssl ♻ .${NC}"
	@echo "${YELLOW}Removed ft_ssl ♻ .${NC}"

re: fclean all
.PHONY: all clean fclean re
