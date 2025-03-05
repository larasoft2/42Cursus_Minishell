# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/22 14:20:31 by racoutte          #+#    #+#              #
#    Updated: 2025/03/05 18:17:30 by lusavign         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

#### VARIABLES #################################################################

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I $(INCLUDE) -I $(LIBDIR)/include
LDFLAGS = -lreadline -lncurses

RM = rm -f

LIBDIR = Libft
LIB = $(LIBDIR)/libft.a
INCLUDE = include
SRC_DIR = src
OBJ_DIR = obj
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
# SRCS = $(wildcard $(SRC_DIR)/**/*.c)
TOTAL_FILES = $(words $(SRCS))
COMPILED_FILES = 0

GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[0;33m
RESET = \033[0m

#### SRC FILES #################################################################

SRCS += src/minishell_loop/main.c
SRCS += src/minishell_loop/init.c
SRCS += src/minishell_loop/check_parsing.c

SRCS += src/builtins/ft_cd.c
SRCS += src/builtins/ft_echo.c
SRCS += src/builtins/ft_env.c
SRCS += src/builtins/ft_exit.c
SRCS += src/builtins/ft_export_utils.c
SRCS += src/builtins/ft_export.c
SRCS += src/builtins/ft_pwd.c
SRCS += src/builtins/ft_unset.c

SRCS += src/environnement/env_basic.c
SRCS += src/environnement/environment_utils.c
SRCS += src/environnement/environment.c
SRCS += src/environnement/environnement_print.c

SRCS += src/error/close_and_free_exit.c
SRCS += src/error/error_message.c
SRCS += src/error/error_message2.c
SRCS += src/error/free.c

SRCS += src/exec/builtins.c
SRCS += src/exec/exec.c
SRCS += src/exec/exit_code.c
SRCS += src/exec/heredoc.c
SRCS += src/exec/open_for_redir.c
SRCS += src/exec/path.c
SRCS += src/exec/pipe_no_redir.c
SRCS += src/exec/pipe_no_redir2.c
SRCS += src/exec/pipe_with_redir.c
SRCS += src/exec/pipe_with_redir2.c
SRCS += src/exec/utils.c
SRCS += src/exec/utils2.c
SRCS += src/exec/utils3.c
SRCS += src/exec/utils4.c

SRCS += src/parsing/final_string_for_exe_add_nodes.c
SRCS += src/parsing/final_string_for_exe_init.c
SRCS += src/parsing/final_string_for_exe.c
SRCS += src/parsing/syntax_error_checker.c
SRCS += src/parsing/syntax_error_empty.c
SRCS += src/parsing/syntax_error_not_handled.c
SRCS += src/parsing/syntax_error_pipe.c
SRCS += src/parsing/syntax_error_quotes.c
SRCS += src/parsing/syntax_error_redir_print_msg.c
SRCS += src/parsing/syntax_error_redir.c
SRCS += src/parsing/tokenize_create_nodes.c
SRCS += src/parsing/tokenize_expand_var_handle_dollar.c
SRCS += src/parsing/tokenize_expand_var_search_replace.c
SRCS += src/parsing/tokenize_expand_var_utils.c
SRCS += src/parsing/tokenize_expand_var.c
SRCS += src/parsing/tokenize_input.c
SRCS += src/parsing/tokenize_list_utils.c
SRCS += src/parsing/tokenize_syntax_error.c
SRCS += src/parsing/tokenize_utils.c
SRCS += src/parsing/tokenize_word_node.c

SRCS += src/signals/signals.c
SRCS += src/signals/signals_utils.c
SRCS += src/signals/signals_heredoc.c

#### RULES ####################################################################

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	@echo "$(YELLOW)🔨 Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIB) $(LDFLAGS)
	@echo "$(GREEN)✅ Build successful!$(RESET)"

$(LIB):
	@echo "$(YELLOW)Adding Libft$(RESET)"
	@$(MAKE) -C $(LIBDIR) > /dev/null 2>&1

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)/environnement $(OBJ_DIR)/error $(OBJ_DIR)/parsing $(OBJ_DIR)/exec $(OBJ_DIR)/minishell_loop $(OBJ_DIR)/builtins $(OBJ_DIR)/signals
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c -I $(INCLUDE) $< -o $@

$(OBJ_DIR)/environnement $(OBJ_DIR)/builtins $(OBJ_DIR)/parsing $(OBJ_DIR)/exec $(OBJ_DIR)/minishell_loop $(OBJ_DIR)/error $(OBJ_DIR)/signals:
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

