/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:25:28 by racoutte          #+#    #+#             */
/*   Updated: 2025/01/08 17:38:43 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

# include "minishell.h"

# define NOT_EMPTY_STRING 0
# define CLOSED_QUOTES 0
# define EMPTY_STRING 1
# define INPUT_ONLY_WHITESPACE 1
# define UNCLOSED_QUOTES 1
# define STARTS_OR_ENDS_WITH_PIPE_REDIR 1
# define WRONG_NUMBER_REDIR 1
# define FIRST_CHARACTER_IS_SPECIAL 1
# define NOT_HANDLED_CHARACTER 1
# define DOUBLE_QUOTE 1
# define SINGLE_QUOTE 1
# define PIPE 1
# define REDIR_IN 2
# define REDIR_OUT 3

// STRUCTURES ///////////////////////////////////////////////////////////////

typedef enum e_token_type
{
	TOKEN_WORD,          // For commands and arguments
	TOKEN_PIPE,          // For '|'
	TOKEN_REDIR_IN,      // For '<'
	TOKEN_REDIR_OUT,     // For '>'
	TOKEN_REDIR_APPEND,  // For '>>'
	TOKEN_REDIR_HEREDOC, // For '<<'
	TOKEN_ENV_VAR,       // For environment variables
	TOKEN_FILENAME
}						t_token_type;

typedef struct s_token_node
{
	t_token_type		type;
	char				*value;
	struct s_token_node	*next;
}						t_token_node;

// FUNCTIONS ////////////////////////////////////////////////////////////////

// SYNTAX_ERROR
int						syntax_error_checker(char *input);
int						check_empty_input(char *input);
int						check_only_whitespace_intput(char *input);
int						check_first_character_is_special_without_error(char *input);
int						not_handled_double_special_character_and(char *input,
							char *open_quote);
int						not_handled_double_pipe(char *input, char *open_quote);
int						not_handled_other_character(char *input,
							char *open_quote);
int						not_handled_char_input(char *input, char *open_quote);
int						input_starts_or_ends_with_pipe(char *input);
int						input_ends_with_redir(char *input);
int						number_redir_right(char *input, char *open_quote);
int						number_redir_left(char *input, char *open_quote);
int						error_message_redir_right(int count);
int						error_message_redir_left(int count);
int						is_quote(char c);
int						check_if_unclosed_quotes(char *input);
int						check_if_not_handled_char_outside_quotes(char *input);

// EXEC UTILS//
void				ft_close_fd(int *pipefd);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strndup(const char *s, size_t n);

// FREE//

#endif
