/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:55:28 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/06 17:07:55 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// export with no options;
// sets environment variables
//
// export can set a null variable that won't show in env
// but will show when typing export
// export alone shows all variables

// export	a = $b
// export b = $a must not loop
//
// export sans $

int	check_if_export_has_arg(char **arg)
{
	size_t	i;

	i = 0;
	while (arg[i])
		i++;
	if (i == 1)
		return (NO_ARGUMENTS);
	return (ARGUMENTS);
}

int	check_if_var_name_already_exists(char *arg, t_env *env)
{
	t_env	*temp;
	char	*new_value;
	char	*key;

	key = extract_key_name(arg);
	if (!key)
		return (EXIT_FAILURE);
	temp = env;
	while (temp != NULL)
	{
		if (ft_strcmp(key, temp->key) == 0)
		{
			new_value = extract_var_value(arg);
			if (!new_value)
				return (EXIT_FAILURE);
			modify_value(new_value, temp);
			free(new_value);
			return (EXIT_SUCCESS);
		}
		temp = temp->next;
	}
	return (EXIT_FAILURE);
}

void	add_var_to_env(char *arg, t_env **env)
{
	char	*key;
	char	*value;

	key = extract_key_name(arg);
	if (!key)
		return;
	value = extract_var_value(arg);
	if (!value)
		value = ft_strdup("");
	if (check_if_var_name_already_exists(key, *env) == EXIT_SUCCESS)
	{
		free(key);
		free(value);
		return ;
	}
	append_list(env, key, value);
	free(key);
	if (value)
		free(value);
}

void	modify_env(char *arg, t_env **env)
{
	if (check_if_var_name_already_exists(arg, *env) == EXIT_SUCCESS)
		return ;
	add_var_to_env(arg, env);
}

void	ft_export(t_exec *exec, t_env **env)
{
	size_t	i;

	i = 1;
	if (check_if_export_has_arg(exec->arg) == NO_ARGUMENTS)
	{
		print_env(*env);
		return ;
	}
	while (exec->arg[i])
	{
		if (check_if_var_name_is_valid(exec->arg[i]) == EXIT_FAILURE)
		{
			print_error_exec_message(NOT_A_VALID_IDENTIFIER, exec->arg[1]);
			return ;
		}
		else
			modify_env(exec->arg[i], env);
		i++;
	}
}
