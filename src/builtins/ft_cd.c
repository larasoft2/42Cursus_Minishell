/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:55:09 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/18 17:28:49 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, char *key)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

void	update_env_var(t_env *env, char *key, char *new_value)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(new_value);
			return ;
		}
		temp = temp->next;
	}
}

void	change_directory_to_home(t_env *env)
{
	char	*home;
	char	*old_pwd;
	char	cwd[1024];

	home = get_env_value(env, "HOME");
	old_pwd = NULL;
	if (!home)
	{
		modify_value_exit_code(1);
		print_error_exec_message(NO_SUCH_FILE_OR_DIRECTORY, "HOME");
		return ;
	}
	old_pwd = get_env_value(env, "PWD");
	if (chdir(home) == 0 && getcwd(cwd, sizeof(cwd)) != NULL)
	{
		update_env_var(env, "OLDPWD", old_pwd);
		update_env_var(env, "PWD", cwd);
	}
	else
		perror("cd");
}

void	handle_dash(t_env *env)
{
	char	*old_pwd;
	char	*current_pwd;
	char	cwd[1024];

	old_pwd = get_env_value(env, "OLDPWD");
	if (!old_pwd)
	{
		modify_value_exit_code(1);
		print_error_exec_message(NO_SUCH_FILE_OR_DIRECTORY, "OLDPWD");
		return ;
	}
	printf("%s\n", old_pwd);
	current_pwd = get_env_value(env, "PWD");
	if (chdir(old_pwd) == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			update_env_var(env, "OLDPWD", current_pwd);
			update_env_var(env, "PWD", cwd);
		}
		else
			perror("getcwd");
	}
	else
		perror("cd");
}

int	ft_cd(t_exec *ex, t_env *env)
{
	char	cwd[1024];

	if (!ex->arg[1] || ft_strcmp(ex->arg[1], "~") == 0)
	{
		change_directory_to_home(env);
		return (modify_value_exit_code(0), EXIT_SUCCESS);
	}
	if (ft_strcmp(ex->arg[1], "-") == 0)
	{
		handle_dash(env);
		return (modify_value_exit_code(0), EXIT_SUCCESS);
	}
	if (chdir(ex->arg[1]) == 0 && getcwd(cwd, 1024) != NULL)
	{
		update_env_var(env, "OLDPWD", get_env_value(env, "PWD"));
		update_env_var(env, "PWD", cwd);
		return (modify_value_exit_code(0), EXIT_SUCCESS);
	}
	else
	{
		perror("cd");
		return (modify_value_exit_code(1), EXIT_SUCCESS);
	}
}

// void	ft_cd(t_exec *ex)
// {
// 	char	*buff;

// 	chdir(ex->arg[1]);
// 	buff = malloc(1024);
// 	if (!buff)
// 		exit(EXIT_FAILURE); //free
// 	printf("%s\n", getcwd(buff, 1024));
//
