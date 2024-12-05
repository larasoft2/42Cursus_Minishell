# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: licohen <licohen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/12 13:57:41 by racoutte          #+#    #+#              #
#    Updated: 2024/12/05 17:31:26 by licohen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

#### VARIABLES #################################################################

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm -f
AR = ar -rcs
HDR_DIR = include
SRC_DIR = src
OBJ_DIR = obj
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

#### SRCS FILES ################################################################

SRCS = src/ft_atoi.c
SRCS += src/ft_bzero.c
SRCS += src/ft_calloc.c
SRCS += src/ft_isalnum.c
SRCS += src/ft_isspace.c
SRCS += src/ft_isalpha.c
SRCS += src/ft_isascii.c
SRCS += src/ft_isdigit.c
SRCS += src/ft_isprint.c
SRCS += src/ft_itoa.c
SRCS += src/ft_memchr.c
SRCS += src/ft_memcmp.c
SRCS += src/ft_memcpy.c
SRCS += src/ft_memmove.c
SRCS += src/ft_memset.c
SRCS += src/ft_putchar.c
SRCS += src/ft_putchar_fd.c
SRCS += src/ft_putendl_fd.c
SRCS += src/ft_putnbr_fd.c
SRCS += src/ft_putstr_fd.c
SRCS += src/ft_split.c
SRCS += src/ft_strchr.c
SRCS += src/ft_strdup.c
SRCS += src/ft_striteri.c
SRCS += src/ft_strjoin.c
SRCS += src/ft_strcat.c
SRCS += src/ft_strlcat.c
SRCS += src/ft_strcpy.c
SRCS += src/ft_strlcpy.c
SRCS += src/ft_strlen.c
SRCS += src/ft_strmapi.c
SRCS += src/ft_strncmp.c
SRCS += src/ft_strnstr.c
SRCS += src/ft_strrchr.c
SRCS += src/ft_strtrim.c
SRCS += src/ft_substr.c
SRCS += src/ft_tolower.c
SRCS += src/ft_toupper.c
SRCS += src/ft_atol.c
SRCS += src/ft_free_and_null.c

SRCS += src/ft_lstnew_bonus.c
SRCS += src/ft_lstadd_front_bonus.c
SRCS += src/ft_lstsize_bonus.c
SRCS += src/ft_lstlast_bonus.c
SRCS += src/ft_lstadd_back_bonus.c
SRCS += src/ft_lstdelone_bonus.c
SRCS += src/ft_lstclear_bonus.c
SRCS += src/ft_lstiter_bonus.c
SRCS += src/ft_lstmap_bonus.c

SRCS += src/ft_printf.c
SRCS += src/ft_pointer_printf.c
SRCS += src/ft_functions_printf.c

SRCS += src/get_next_line.c
SRCS += src/get_next_line_utils.c

#### RULES #####################################################################

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c -I $(HDR_DIR) $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
