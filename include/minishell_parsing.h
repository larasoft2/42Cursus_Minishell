/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:25:28 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/18 18:12:26 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

# include "minishell_exec.h"
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
# define MAX_ARGS 50

// STRUCTURES ///////////////////////////////////////////////////////////////

typedef enum e_token_type
{
	TOKEN_WORD,          	// For single word
	TOKEN_PIPE,          	// For '|'
	TOKEN_REDIR_IN,      	// For '<'
	TOKEN_REDIR_OUT,     	// For '>'
	TOKEN_REDIR_APPEND,  	// For '>>'
	TOKEN_REDIR_HEREDOC, 	// For '<<'
	TOKEN_CMD_WITH_OPTIONS, // For commands and arguments
}						t_token_type;

typedef struct s_token_node
{
	t_token_type		type;
	char				*value;
	//int					to_delete;
	struct s_token_node	*next;
}						t_token_node;

struct s_env;
typedef struct s_env t_env;

struct s_exec;
typedef struct s_exec t_exec;

// FUNCTIONS ////////////////////////////////////////////////////////////////

// SYNTAX_ERROR
int				syntax_error_checker(char *input);
int				check_empty_input(char *input);
int				check_only_whitespace_intput(char *input);
int				check_first_character_is_special_without_error(char *input);
int				not_handled_double_special_character_and(char *input,
					char *open_quote);
int				not_handled_double_pipe(char *input, char *open_quote);
int				not_handled_other_character(char *input,
					char *open_quote);
int				not_handled_char_input(char *input, char *open_quote);
int				handle_redir_symbol(char *input, size_t *i, int *count,
					char symbol);
int				input_starts_or_ends_with_pipe(char *input);
int				input_ends_with_redir(char *input);
int				number_redir_right(char *input, char *open_quote);
int				number_redir_left(char *input, char *open_quote);
int				error_message_redir_right(int count);
int				error_message_redir_left(int count);
int				count_redir(char symbol, int *count);
int				is_quote(char c);
int				check_if_unclosed_quotes(char *input);
int				check_if_not_handled_char_outside_quotes(char *input);

// TOKENIZE
int				is_pipe_redirin_redirout_character(char c);
t_token_node	*create_token_node(t_token_type type, char *value);
void			add_token(t_token_node **list, t_token_node *new_token);
char			*read_word(char *input, int *i);
t_token_node	*tokenize_input(char *input);
void			create_word_node(char *input, int *i,
					t_token_node **token_list);
void			create_special_node(char *input, int *i,
					t_token_node **token_list);
void			create_pipe_node(int *i, t_token_node **token_list);
void			create_redir_in_node(char *input, int *i,
					t_token_node **token_list);
void			create_redir_out_node(char *input, int *i,
					t_token_node **token_list);
void			create_redir_append_node(char *input, int *i,
					t_token_node **token_list);
void			create_heredoc_node(char *input, int *i,
					t_token_node **token_list);
void			skip_spaces(char *input, int *i);
int				check_error_token_pipe(t_token_node *token_list);
int				check_error_token_redir(t_token_node *token_list);
int				check_error_token(t_token_node *token_list);
void			print_error_token(t_token_node *token_list);

// EXPANDER
char			*expand_env_var(char *name, t_env **env);
void			update_index(int *i, char *word);
char			*extract_name_after_dollar(char *input, int *i);
char			*str_append(char *str, char c);
char			*handle_quote(char *input, int *i, char *open_quote,
					char *final_string);
char			*handle_dollar_sign(char *input, int *i, t_env **env,
					char *expanded_var);
char			*handle_exit_error(char *final_string, int *i);
char			*expand(char *final_string, char *input, int *i, t_env **env);
char			*handle_special_case(char *input, int *i, char open_quote,
					char *final_string);
char			*dollar_special_cases(char *input, int *i, char open_quote,
					char *final_string);
char			*search_and_replace(char *input, t_env **env);
char			*search_and_replace_heredoc(char *input);
int				process_regular_token(t_token_node *token, t_env **env_final);
int				process_heredoc_token(t_token_node *token);
t_token_node	*clean_tokens(t_token_node **token_list, t_env **env_final);
int				is_metacharacter(char c);
int				is_var_stop_char(char c);
void			update_index(int *i, char *word);

// FINAL_EXEC_LIST
void			init_exec_node(t_exec *new_node,
					t_token_type type, char *value);
t_exec			*add_exec_node_with_type(t_exec **exec_list,
					t_token_type type, char *value);
void			add_word(char **arg, char *value, int i);
t_exec			*add_word_to_exec_word_node(t_exec **exec_list, char *value,
					int *word_count, t_exec **last_exec_node);
void			handle_token_word(t_exec **exec_list, t_token_node *current_token,
					int *word_count, t_exec **last_exec_node);
void			handle_token_special(t_exec **exec_list, t_token_node *current_token,
					int *word_count, t_exec **last_exec_node);
t_exec			*add_all_tokens(t_token_node **token_list, t_exec **exec_list);

// PRINT
void			print_tokens(t_token_node *list); // A ENLEVER A LA FIN
void			print_tokens_exec_list(t_exec *exec_list); // A ENLEVER A LA FIN

#endif
