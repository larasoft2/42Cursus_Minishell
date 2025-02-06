/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:55:24 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/06 18:34:26 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// // exit with no options.
// exits the shell

// static int	is_len_one(int fd_out)
// {
// 	ft_putendl_fd("exit", fd_out);
// 	return (0);
// }

// static int	not_num(void)
// {
// 	ft_putendl_fd("minishell: exit: numeric argument required", 2);
// 	return (2);
// }

// static int	too_many_args(void)
// {
// 	ft_putendl_fd("minishell: exit: too many arguments", 2);
// 	return (1);
// }

// static int	is_num(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (ft_isspace(str[i]))
// 		i++;
// 	if (str[i] == '-' || str[i] == '+')
// 		i++;
// 	if (!str[i])
// 		return (0);
// 	while (ft_isdigit(str[i]))
// 		i++;
// 	if (str[i])
// 		return (0);
// 	return (1);
// }

// int	ft_exit(t_exec *ex, int fd_out)
// {
// 	int len;
// 	int code;

// 	len = nbr_of_args(ex);
// 	if (len == 1)
// 		return (is_len_one(fd_out));
// 	else if (!is_num(ex->arg[1]))
// 		return (not_num());
// 	else if (len > 2)
// 		return (too_many_args());
// 	code = ft_atoi(ex->arg[1]) % 256;
// 	if (code < 0)
// 		code += 256;
// 	ft_putendl_fd("exit", fd_out);
// 	return (code);
// }

int ft_exit(t_exec **ex, t_env **env)
{
	printf("Hello\n");
	free_env_list(env);
	free_exec_list(ex);
	printf("Hello 2\n");
	print_env(*env);
	print_tokens_exec_list(*ex);
	printf("Hello 3\n");
	exit(0);
}
