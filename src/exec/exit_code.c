/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:49:40 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/18 17:50:00 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long	*get_exit_status(void)
{
	static long	exit_status;

	return (&exit_status);
}

void	modify_value_exit_code(long code)
{
	long	*exit_status;

	exit_status = get_exit_status();
	*exit_status = code;
}
