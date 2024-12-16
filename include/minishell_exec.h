/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:26:15 by racoutte          #+#    #+#             */
/*   Updated: 2024/12/16 19:07:09 by lusavign         ###   ########.fr       */
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
	char	*cmd; //contain cmd ("ls", "echo", ...)
	char	**arg; //arr contains args for one cmd {ls "-l", grep "txt", ...}
	t_filenames	*redirs; //list of redirs

	int	fd_in; //fd for stdin
	int	fd_out; //fd for stdout
	struct s_exec *next; //next cmd
}	t_exec;

typedef struct s_filenames
{
	char	*path; //path to file (ex: file.txt)
	t_token_type type; //type of redir associated to file (int, out etc)
	struct s_filenames	*next; //next file in list
}	t_filenames;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

 //BUILTINS//
int					ft_echo(t_exec *ex, int fd_out);
int					ft_pwd(int fd_out);
int					ft_unset(t_env *env, t_exec *ex);

void				ft_env(t_env *env);

//EXEC UTILS//
int					ft_strcmp(char *s1, char *s2);
int					nbr_of_args(t_exec *ex)

#endif