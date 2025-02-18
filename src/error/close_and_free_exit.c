/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_free_exit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:30:32 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/18 17:32:44 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_and_free_before_exit(t_env *env, t_exec *ex, int *std_dup)
{
	free_env_list(&env);
	free_exec_list(&ex);
	close(std_dup[0]);
	close(std_dup[1]);
}
