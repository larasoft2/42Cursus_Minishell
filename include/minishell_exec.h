/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:26:15 by racoutte          #+#    #+#             */
/*   Updated: 2024/12/10 21:55:32 by lusavign         ###   ########.fr       */
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

// Built-in functions

typedef struct s_ast
{
	t_token_type	type;

	char			**arg;

	struct s_ast	*right;
	struct s_ast	*left;
}					t_ast;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

void				ft_env(t_env *env);
int					ft_echo(t_ast *ast, int fd_out);
int					ft_exit(t_ast *ast, int fd_out);
int					ft_pwd(int fd_out);
int					nbr_of_args(t_ast *ast);
int					ft_strcmp(char *s1, char *s2);

#endif