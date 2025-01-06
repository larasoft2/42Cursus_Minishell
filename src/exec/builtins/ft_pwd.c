/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:55:39 by lusavign          #+#    #+#             */
/*   Updated: 2025/01/16 18:25:45 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

int	ft_pwd(int fd_out)
{
	char dir[4096]; // posix max

	if (getcwd(dir, 4096))
	{
		if (fd_out >= 0) // securite pas necessaire si handled in parsing
		{
			ft_putendl_fd(dir, fd_out);
			return (0);
		}
	}
	ft_putendl_fd("pwd: error retrieving current directory", 2);
	return (1);
}
