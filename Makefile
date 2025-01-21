# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/22 14:20:31 by racoutte          #+#    #+#              #
#    Updated: 2025/01/21 17:38:46 by lusavign         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

#### VARIABLES #################################################################

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -lreadline -lncurses

RM = rm -f

LIBDIR = Libft
LIB = $(LIBDIR)/libft.a
INCLUDE = include
SRC_DIR = src
OBJ_DIR = obj
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
SRCS = $(wildcard $(SRC_DIR)/**/*.c)
TOTAL_FILES = $(words $(SRCS))
COMPILED_FILES = 0

GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[0;33m
RESET = \033[0m

#### SRC FILES #################################################################

# SRCS += src/minishell_loop/main.c

# SRCS += src/parsing/syntax_error.c

# SRCS += src/exec/built_in.c


#### RULES ####################################################################

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	@echo "$(YELLOW)🔨 Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIB) $(LDFLAGS)
	@echo "$(GREEN)✅ Build successful!$(RESET)"

$(LIB):
	@echo "$(YELLOW)Adding Libft$(RESET)"
	@$(MAKE) -C $(LIBDIR) > /dev/null 2>&1

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)/environnement $(OBJ_DIR)/error $(OBJ_DIR)/parsing $(OBJ_DIR)/builtins $(OBJ_DIR)/exec $(OBJ_DIR)/minishell_loop
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c -I $(INCLUDE) $< -o $@

$(OBJ_DIR)/environnement $(OBJ_DIR)/parsing $(OBJ_DIR)/exec $(OBJ_DIR)/builtins $(OBJ_DIR)/minishell_loop $(OBJ_DIR)/error:
	@mkdir -p $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(YELLOW)🧹 Cleaning object files...$(RESET)"
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIBDIR) clean > /dev/null 2>&1
	@echo "$(GREEN)✓ Cleaned$(RESET)"

fclean: clean
	@echo "$(YELLOW)🗑️ Full cleanup...$(RESET)"
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBDIR) fclean > /dev/null 2>&1
	@echo "$(GREEN)✓ Fully cleaned$(RESET)"

re: fclean all

.PHONY: all clean fclean re
