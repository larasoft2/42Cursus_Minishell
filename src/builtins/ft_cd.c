/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:55:09 by lusavign          #+#    #+#             */
/*   Updated: 2025/01/23 15:03:49 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cd with only relative or absolute	path;
// changes the current working directory

// chdir

void	ft_cd(t_exec *ex)
{
	char	*buff;

	printf("I'm in cd\n");
	chdir(ex->arg[1]);
	buff = malloc(1024);
	printf("%s\n", getcwd(buff, 1024));
}

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	t_exec ex;
// 	char *args[] = {av[1], NULL};

// 	ex.arg = args;
// 	ft_cd(&ex);
// }