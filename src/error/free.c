/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:25:00 by racoutte          #+#    #+#             */
/*   Updated: 2024/12/18 15:16:35 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token_node *list)
{
	t_token_node *temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp->value);
		free(temp);
	}
}
