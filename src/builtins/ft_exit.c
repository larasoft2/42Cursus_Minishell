/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:55:24 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/18 17:50:37 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *str)
{
	size_t	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (EXIT_FAILURE);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

long	calculate_exit_code(long nb)
{
	long	exit_code;

	exit_code = 0;
	if (nb >= 0)
		exit_code = nb % 256;
	else
		exit_code = 256 - ((-nb) % 256);
	return (exit_code);
}

void	exec_exit_with_code(t_exec *ex, t_env *env, int *std_dup,
		long *exit_code)
{
	*exit_code = calculate_exit_code(ft_atol(ex->arg[1]));
	modify_value_exit_code(*exit_code);
	close_and_free_before_exit(env, ex, std_dup);
}

int	ft_exit(t_exec *ex, t_env *env, int *std_dup)
{
	long	*exit_code;
	int		len_cmd;

	len_cmd = nbr_of_args(ex);
	exit_code = get_exit_status();
	printf("exit\n");
	if (!ex->arg[1])
	{
		close_and_free_before_exit(env, ex, std_dup);
		exit(*exit_code);
	}
	if (is_numeric(ex->arg[1]) == EXIT_FAILURE || ft_atol(ex->arg[1]) > INT_MAX
		|| ft_atol(ex->arg[1]) < INT_MIN)
	{
		print_error_exec_message(NUMERIC_ARGUMENT_REQUIRED, ex->arg[1]);
		close_and_free_before_exit(env, ex, std_dup);
		exit(2);
	}
	if (len_cmd > 2)
	{
		print_error_exec_message(TOO_MANY_ARGUMENTS, ex->arg[0]);
		return (modify_value_exit_code(1), EXIT_FAILURE);
	}
	exec_exit_with_code(ex, env, std_dup, exit_code);
	exit(*exit_code);
}
