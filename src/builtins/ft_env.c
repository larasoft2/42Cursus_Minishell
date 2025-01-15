/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:29:09 by lusavign          #+#    #+#             */
/*   Updated: 2025/01/15 17:23:05 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *env)
{
	if (!env)
		exit(1); //idk si exit
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}