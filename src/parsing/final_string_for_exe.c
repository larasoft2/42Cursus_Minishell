/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_string_for_exe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:30:59 by racoutte          #+#    #+#             */
/*   Updated: 2025/01/17 14:59:04 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_exec	*add_all_tokens(t_token_node **token_list)
{
	t_exec			*exec_list;
	t_token_node	*current_token;

	exec_list = NULL;
	current_token = *token_list;
	while (current_token != NULL)
	{
		if (current_token->type == TOKEN_WORD) // all TOKEN_WORD into a single node = CMD with OPTIONS
		{
			create_exec_word_node(&exec_list, TOKEN_WORD, current_token->value);
			append_exec_node(&exec_list);
		}
		else if (current_token->type == TOKEN_PIPE
				|| current_token->type == TOKEN_REDIR_IN
				|| current_token->type == TOKEN_REDIR_OUT
				|| current_token->type == TOKEN_REDIR_APPEND
				|| current_token->type == TOKEN_REDIR_HEREDOC)
		{
			create_exec_node_with_type(&exec_list, current_token->type, current_token->value);
			append_exec_node(&exec_list);
		}
		current_token = current_token->next;
	}
	return (exec_list);
}

t_exec	*get_final_list_for_exec(t_token_node **token_list)
{
	t_exec			*final_exec_list;

	if (!token_list || !(*token_list))
		return (NULL);
	final_exec_list = (t_exec *)malloc(sizeof(t_exec));
	if (!final_exec_list)
	{
		ft_putstr_fd("Error: malloc final_exec_list failed\n", STDERR_FILENO);
		return (NULL);
	}
	final_exec_list = add_all_tokens(token_list);
	return (final_exec_list);
}
