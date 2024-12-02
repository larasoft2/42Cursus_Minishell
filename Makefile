# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/22 14:20:31 by racoutte          #+#    #+#              #
#    Updated: 2024/11/25 11:58:35 by racoutte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

#### VARIABLES #################################################################

CC = cc
CFLAGS = -Wall -Wextra -Werror

# ifeq ($(d), 1)
# 	CFLAGS += -fsanitize=thread
# endif

RM = rm -f

INCLUDE = include
SRC_DIR = src
OBJ_DIR = obj
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
TOTAL_FILES = $(words $(SRCS))
COMPILED_FILES = 0

GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[0;33m
RESET = \033[0m

#### SRC FILES #################################################################

SRCS += src/main.c

#### RULES ####################################################################

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)🔨 Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✅ Build successful!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c -I $(INCLUDE) $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@echo "$(YELLOW)🧹 Cleaning object files...$(RESET)"
	@$(RM) -r $(OBJ_DIR)
	@echo "$(GREEN)✓ Cleaned$(RESET)"

fclean: clean
	@echo "$(YELLOW)🗑️ Full cleanup...$(RESET)"
	@$(RM) $(NAME)
	@echo "$(GREEN)✓ Fully cleaned$(RESET)"

re: fclean all

.PHONY: all clean fclean re