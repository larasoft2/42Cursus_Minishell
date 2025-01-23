/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:29:09 by lusavign          #+#    #+#             */
/*   Updated: 2025/01/23 18:14:58 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//si export test > creer variable avec valeur NULL (ne s'affichera pas dans env)
//si export test= > creer variable avec valeur \0

void	ft_env(t_env *env)
{
	if (!env)
		exit(1); //idk si exit (also free)
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}