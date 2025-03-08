/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 23:30:45 by lusavign          #+#    #+#             */
/*   Updated: 2025/03/05 21:23:51 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "minishell.h"
# include "minishell_parsing.h"
# include <stdbool.h>

# define CD 0
# define ECHO 1
# define ENV 2
# define EXIT 3
# define EXPORT 4
# define PWD 5
# define UNSET 6
# define ARGUMENTS 0
# define NO_ARGUMENTS 1

typedef struct s_exec
{
	char			*hd_name;
	char			**arg;
	int				fd_in;
	int				fd_out;
	long			exit_status;
	t_token_type	type;
	struct s_exec	*next;
}					t_exec;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_ex_ctx
{
	int			fd_in;
	int			pipefd[2];
	int			std_dup[2];
	bool		has_command;
	pid_t		pid;
	t_exec		*ex;
	t_exec		*block_begin;
	t_exec		*current;
	t_exec		*begin;
}					t_ex_ctx;

// BUILTINS//
int					ft_echo(t_exec *ex);
int					ft_pwd(int fd_out);
int					ft_unset(t_exec *ex, t_env **env);
int					ft_cd(t_exec *ex, t_env *env);
int					ft_env(t_exec *ex, t_env *env);
int					ft_export(t_exec *exec, t_env **env);
void				add_var_to_env(char *arg, t_env **env);
int					ft_exit(t_exec *ex, t_env *env, int *std_dup);
int					check_if_cmd_has_arg(char **arg);
int					check_if_var_name_is_valid(char *arg);

long				*get_exit_status(void);

char				*extract_key_name(char *arg);
char				*extract_var_value(char *arg);

void				modify_value_exit_code(long code);
void				modify_value(char *new_value, t_env *env_var);

// EXEC UTILS//
bool				check_command_in_list(t_exec *ex);
bool				check_cmd_in_block(t_exec *begin, t_exec *end);

int					env_list_size(t_env *env);
int					ft_strcmp(char *s1, char *s2);
int					nbr_of_args(t_exec *ex);
int					count_command(t_exec *ex);
int					has_pipe(t_exec *ex);
int					has_redir(t_exec *ex);
int					has_heredoc(t_exec *ex);
int					print_error(char *filename);

char				*ft_strndup(const char *s, size_t n);

void				get_exit_code(int status);
void				init_fd_dup(t_exec *ex, int *std_dup);
void				ft_close_fds(int fd);
void				ft_close_fd(int *pipefd);
int					print_perm(char *command);
void				print_command_not_found(char *command);
void				print_delimiter_error_message(char *delimiter);
void				restore_fds(int *std_dup);
void				skip_redirections(t_exec **current);

t_exec				*get_next_exec_token(t_exec *ex);
t_exec				*find_next_valid_token(t_exec *ex);

// EXEC//
int					exec_builtin(t_exec *ex, t_env **env, int *std_dup);
int					ft_open(t_exec *ex, int *fd_in);
int					handle_heredoc(t_exec *ex);
int					handle_redir(t_exec *ex);
int					handle_redir_in_pipe(t_exec *ex, int pipefd);
int					is_builtin(t_exec *ex);
int					redir_in(t_exec *ex, int *fd_in);
int					redir_out(t_exec *ex, int *fd_in);
int					setup_pipe_redir(int pipefd[2]);
int					starting_hd(t_exec *ex, int *std_dup);

char				*get_path(t_env *env, char *cmd, t_exec *ex);
char				*is_path_exec(char *cmd, char **full_paths);
char				**put_env_in_ar(t_env *envp);

void				init_ex_ctx(t_ex_ctx *ex_ctx, t_exec *ex);
void				init_ex_ctx_for_redir(t_ex_ctx *ex_ctx,
						t_exec *ex, int *std_dup);
void				ft_exec(t_exec *ex, t_env **env,
						pid_t *pid, t_ex_ctx *ex_ctx);
void				ft_fork(t_exec *cmd, t_env **env, int *std_dup);
void				ft_open_heredocs(t_exec *ex, int pipefd);
void				ft_process(t_env **env, t_exec *ex);
void				handle_empty_pipe(t_ex_ctx *ex_ctx);
void				handle_pipes_if_redir(t_exec *ex, t_env **env,
						int *std_dup);
void				handle_pipes_no_redir(t_exec *ex, t_env **env,
						int *std_dup, int count);
void				handle_parent_io(int *fd_in, int *pipefd);
void				handle_child_io(int fd_in, int *pipefd);
void				setup_pipe_no_redir(int *pipefd, t_exec *ex);
void				setup_io_for_command(t_ex_ctx *ex_ctx);

// FREE//
void				*ft_free_array(char **ar);
void				free_ex_or_struct(t_exec *ex, t_ex_ctx *ex_ctx);
void				free_for_ft_exec(t_env **env, char **env_ar,
						char *path, pid_t *pid);

#endif
