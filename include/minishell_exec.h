/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:26:15 by racoutte          #+#    #+#             */
/*   Updated: 2025/01/15 17:19:41 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include "minishell.h"
# include "minishell_parsing.h"

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
	t_token_node *type;  // list of redirs
	int fd_in;           // fd for stdin
	int fd_out;          // fd for stdout
	struct s_exec *next; // next cmd
}					t_exec;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

// BUILTINS//
int					ft_echo(t_exec *ex, int fd_out);
int					ft_pwd(int fd_out);
int					ft_unset(t_env *env, t_exec *ex);

void				ft_env(t_env *env);

// EXEC UTILS//
int					ft_strcmp(char *s1, char *s2);
int					nbr_of_args(t_exec *ex);
char				*ft_strndup(const char *s, size_t n);

// EXEC//
int					is_builtin(t_exec *ex);

#endif
