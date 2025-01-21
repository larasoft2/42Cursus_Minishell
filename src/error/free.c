/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:25:00 by racoutte          #+#    #+#             */
/*   Updated: 2025/01/15 18:04:01 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token_node *list)
{
	t_token_node *temp;

	while (list)
	{
		temp = list;
		if (list->next == NULL)
			break ;
		list = list->next;
		free(temp->value);
		free(temp);
	}
}
