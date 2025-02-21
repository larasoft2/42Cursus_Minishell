/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:08:01 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/21 23:51:57 by lusavign         ###   ########.fr       */
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
	struct s_exec *next;
}					t_exec;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_struct
{

    int 		fd_in;
    int			pipefd[2];
	t_exec		*ex;
    t_exec		*current;
} t_struct;

// BUILTINS//
int					ft_echo(t_exec *ex);
int					ft_pwd(int fd_out);
int					ft_unset(t_exec *ex, t_env **env);
int					ft_cd(t_exec *ex, t_env *env);
int					ft_env(t_exec *ex, t_env *env);
int					ft_export(t_exec *exec, t_env **env);
int					ft_exit(t_exec *ex, t_env *env, int *std_dup);
int					check_if_cmd_has_arg(char **arg);
int					check_if_var_name_is_valid(char *arg);

long				*get_exit_status(void);

char				*extract_key_name(char *arg);
char				*extract_var_value(char *arg);

void				modify_value_exit_code(long code);
void				modify_value(char *new_value, t_env *env_var);

// EXEC UTILS//
int					ft_strcmp(char *s1, char *s2);
int					nbr_of_args(t_exec *ex);
int					count_command(t_exec *ex);
int					has_pipe(t_exec *ex);
int					has_redir(t_exec *ex);
int					has_heredoc(t_exec *ex);

char				*ft_strndup(const char *s, size_t n);

void				ft_init(t_exec *ex, int *std_dup);
void    			restore_fds(int *std_dup);
void				ft_close_fds(int fd);
void				ft_close_fd(int *pipefd);
void    			ft_open(t_exec *ex, int *fd_in);
void				ft_open_heredocs(t_exec *ex, int pipefd);

t_exec				*get_next_exec_token(t_exec *ex);
t_exec				*find_next_valid_token(t_exec *ex);

// EXEC//
int					exec_builtin(t_exec *ex, t_env **env, int *std_dup);
int					is_builtin(t_exec *ex);
int					handle_heredoc(t_exec *ex);

char				**put_env_in_ar(t_env *envp);
char				*is_path_exec(char *cmd, char **full_paths);
char				*get_path(t_env *env, char *cmd);
void				redir_out(t_exec *ex);
void				redir_in(t_exec *ex, int *fd_in);
void				handle_redir(t_exec *ex);
void				handle_redir_in_pipe(t_exec *ex, int pipefd);
void				handle_pipes_no_redir(t_exec *ex, t_env **env, int *std_dup);
void				ft_exec(t_exec *ex, t_env **env);
void				ft_fork(t_exec *cmd, t_env **env, int *std_dup);
void    			ft_process(t_env **env, t_exec *ex);

// FREE//
void				*ft_free_array(char **ar);

#endif
