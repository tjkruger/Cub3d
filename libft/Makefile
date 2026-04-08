# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/17 14:50:42 by tjkruger          #+#    #+#              #
#    Updated: 2025/11/17 15:07:46 by tjkruger         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_NAME = libft.a
LIBFT_DIR = .
INC_DIR = include
OBJ_DIR = obj
SRCS = ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
       ft_isprint.c ft_memset.c ft_strlen.c ft_memcpy.c ft_memmove.c \
       ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
       ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
       ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c \
       ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
       ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
CC = cc
CFLAGS = -Wall -Wextra -Werror -I../$(INC_DIR)

all: $(LIBFT_NAME)

$(LIBFT_NAME): $(OBJ)
	ar rcs $@ $(OBJ)
	@echo "✨ libft built successfully!"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(LIBFT_NAME)

re: fclean all

.PHONY: all clean fclean re
