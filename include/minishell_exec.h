/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:26:15 by racoutte          #+#    #+#             */
/*   Updated: 2024/12/10 15:59:41 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include "minishell.h"

# define CD 0
# define ECHO 1
# define ENV 2
# define EXIT 3
# define EXPORT 4
# define PWD 5
# define UNSET 6

//Built-in functions

int ft_echo(char **array, int fd_out);
int ft_exit(char **array, int fd_out);
int ft_pwd(int fd_out);
int ft_cd(char **array);
int nbr_of_args(char **array);


MODIF !!!!

#endif