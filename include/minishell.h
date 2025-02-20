/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/02/20 15:43:56 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include "libft.h"
# include "minishell_exec.h"
# include "minishell_parsing.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>

extern int g_signal;

// STRUCTURES ///////////////////////////////////////////////////////////////
typedef enum e_error
{
	SYNTAX_ERROR_REDIR_SINGLE_RIGHT,
	SYNTAX_ERROR_REDIR_DOUBLE_RIGHT,
	SYNTAX_ERROR_REDIR_SINGLE_LEFT,
	SYNTAX_ERROR_REDIR_DOUBLE_LEFT,
	SYNTAX_ERROR_PIPE_SINGLE,
	SYNTAX_ERROR_NEWLINE,
	SYNTAX_ERROR_UNCLOSED_QUOTES,
	SYNTAX_ERROR_NOT_HANDLED,
	SYNTAX_ERROR_NOT_HANDLED_WORD,

	COMMAND_NOT_FOUND,
	NOT_A_VALID_IDENTIFIER,
	NO_SUCH_FILE_OR_DIRECTORY,
	NUMERIC_ARGUMENT_REQUIRED,
	INVALID_OPTION,
	TOO_MANY_ARGUMENTS,
}		t_error;

// FUNCTIONS ////////////////////////////////////////////////////////////////

// ERROR
void	print_error_syntax_message(t_error error);
void	print_error_not_handled(char c);
void	print_error_not_handled_word(char *word);
char	*get_error_exec_message(t_error error);
void	print_error_exec_message(t_error error, char *word);

// FREE
void	free_token_list(t_token_node **list);
void	free_env_list(t_env **list);
void	free_exec_list(t_exec **list);
void	close_and_free_before_exit(t_env *env, t_exec *ex, int *std_dup);

// INIT
void	init_struct(t_token_node *token_list);

// MINISHELL LOOP
int		parsing(char *input, t_token_node **token_list, t_env **env_final);
int		check_syntax_input(char *input, int *syntax_status);
int		tokenize_parsing(char *input, t_token_node **token_list,
			t_env **env_final, t_exec **exec_list);

// ENVIRONMENT
void	append_list(t_env **head, char *key, char *value);
t_env	*get_env_list(char **realenv);
void	print_env(t_env *env);

// SIGNALS
void	setup_default_signals_handling(void);
void	setup_main_prompt_signals_handling(void);
void	setup_heredoc_signals_handling(void);
void	setup_command_mode_signals_handling(void);
void	sigint_handler(int sig);
void	sigint_prompt(int sig);
void	sigint_heredoc(int sig);
void	sigquit_handler(int sig);
void	sigpipe_handler(int sig);

#endif
