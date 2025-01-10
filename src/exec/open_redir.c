/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:37:43 by lusavign          #+#    #+#             */
/*   Updated: 2025/01/10 18:56:58 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_open(char **av, int filetype, int pipefd)
{
    //pas d'open pour word
    if (ex->type == TOKEN_PIPE)
        blabla;
    if (ex->type == TOKEN_REDIR_IN)
        blabla; //o rdonly
    if (ex->type == TOKEN_REDIR_OUT)
        blabla; //o creat
    if (ex->type == TOKEN_REDIR_APPEND)
        blabla;
    if (ex->type == TOKEN_REDIR_HEREDOC)
        blabla;
}