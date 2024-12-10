/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:55:39 by lusavign          #+#    #+#             */
/*   Updated: 2024/12/10 21:15:26 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

/*
** ft_pwd : built-in pwd
** affiche le chemin du repertoire courant
*/

// pwd with no	options;
// prints the current working directory

int	ft_pwd(int fd_out)
{
	char dir[4096];

	if (getcwd(dir, 4096))
	{
		ft_putendl_fd(dir, fd_out);
		return (0);
	}
	ft_putendl_fd("pwd: error retrieving current directory", 2);
	return (1);
}