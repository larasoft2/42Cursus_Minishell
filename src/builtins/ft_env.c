/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:29:09 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/18 17:29:28 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_exec *ex, t_env *env)
{
	if (ex->arg[1] != NULL)
	{
		print_error_exec_message(NO_SUCH_FILE_OR_DIRECTORY, ex->arg[1]);
		return (modify_value_exit_code(127), EXIT_FAILURE);
	}
	print_env(env);
	return (modify_value_exit_code(0), EXIT_SUCCESS);
}
