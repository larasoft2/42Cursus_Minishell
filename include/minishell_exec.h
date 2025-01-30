/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/01/29 15:35:33 by lusavign         ###   ########.fr       */
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

typedef struct s_exec
{
	char **arg;          // contains args for one cmd {ls "-l", ...}
	t_token_type type;  // list of redirs
	int fd_in;           // fd for stdin
	int fd_out;          // fd for stdout
	int	error;
	struct s_exec *next; // next cmd
}					t_exec;


typedef struct s_env
{
	char			*key;
	char			*value;
	bool			exportable;
	struct s_env	*next;
}					t_env;

// BUILTINS//
int					ft_echo(t_exec *ex, int fd_out);
int					ft_pwd(int fd_out);
int					ft_unset(t_env **env, t_exec *ex);
void				ft_cd(t_exec *ex);
void				ft_env(t_env *env);

// EXEC UTILS//
void				ft_close_fd(int *pipefd);
int					ft_strcmp(char *s1, char *s2);
int					nbr_of_args(t_exec *ex);
int					count_command(t_exec *ex);
char				*ft_strndup(const char *s, size_t n);


// EXEC//
int					exec_builtin(t_exec *ex, t_env **env);
int					is_builtin(t_exec *ex);
void				ft_fork(t_exec *cmd, t_env **env, int *pipefd);
char				**put_env_in_ar(t_env *envp);
void    			ft_process(t_env **env, t_exec *ex);

// FREE//
void				*ft_free_array(char **ar);
char				**put_env_in_ar(t_env *envp);
char				*is_path_exec(char *cmd, char **full_paths);
char				*get_path(t_env *env, char *cmd);

// FREE//
void				*ft_free_array(char **ar);

#endif