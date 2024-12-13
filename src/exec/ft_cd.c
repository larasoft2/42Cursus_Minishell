/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:55:09 by lusavign          #+#    #+#             */
/*   Updated: 2024/12/13 18:18:36 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

// cd with only relative or absolute	path;
// changes the current working directory

// chdir

void	ft_cd(t_ast *ast)
{
	char	*buff;

	chdir(ast->arg[0]);
	buff = malloc(1024);
	printf("%s\n", getcwd(buff, 1024));
}

int	main(int ac, char **av)
{
	(void)ac;
	t_ast ast;
	char *args[] = {av[1], NULL};

	ast.arg = args;
	ft_cd(&ast);
}