/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:12:09 by licohen           #+#    #+#             */
/*   Updated: 2024/12/03 15:46:00 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

/*
** ft_pwd : built-in pwd
** affiche le chemin du repertoire courant
*/

int ft_pwd(void)
{
    char    dir[4096];
    
    if (getcwd(dir, 4096))
    {
        ft_putendl_fd(dir, 1);
        return (0);
    }
    ft_putendl_fd("pwd: error retrieving current directory", 2);
    return (1);
}
