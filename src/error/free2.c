/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:17:08 by lusavign          #+#    #+#             */
/*   Updated: 2025/03/05 21:23:34 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ex_or_struct(t_exec *ex, t_ex_ctx *ex_ctx)
{
	if (ex_ctx)
		free_exec_list(&ex_ctx->begin);
	else
		free_exec_list(&ex);
}
