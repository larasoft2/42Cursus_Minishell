/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_string_for_exe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:30:59 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/04 17:32:09 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_token_word(t_exec **exec_list, t_token_node *current_token,
	int *word_count, t_exec **last_exec_node)
{
	if (current_token->type == TOKEN_WORD)
	{
		add_word_to_exec_word_node(exec_list, current_token->value,
			word_count, last_exec_node);
	}
}

void	handle_token_special(t_exec **exec_list, t_token_node *current_token,
	int *word_count, t_exec **last_exec_node)
{
	if (current_token->type == TOKEN_REDIR_IN
		|| current_token->type == TOKEN_REDIR_OUT
		|| current_token->type == TOKEN_REDIR_APPEND
		|| current_token->type == TOKEN_REDIR_HEREDOC)
	{
		add_exec_node_with_type(exec_list, current_token->type,
			current_token->value);
	}
	else if (current_token->type == TOKEN_PIPE)
	{
		add_exec_node_with_type(exec_list, current_token->type,
			current_token->value);
		*word_count = 0;
		*last_exec_node = NULL;
	}
}

t_exec	*add_all_tokens(t_token_node **token_list)
{
	t_exec			*exec_list;
	t_exec			*last_exec_node;
	t_token_node	*current_token;
	int				word_count;

	exec_list = NULL;
	last_exec_node = NULL;
	current_token = *token_list;
	word_count = 0;
	while (current_token != NULL)
	{
		handle_token_word(&exec_list, current_token, &word_count,
			&last_exec_node);
		handle_token_special(&exec_list, current_token, &word_count,
			&last_exec_node);
		current_token = current_token->next;
	}
	return (exec_list);
}

// t_exec	*add_all_tokens(t_token_node **token_list)
// {
// 	t_exec			*exec_list;
// 	t_exec			*last_exec_node;
// 	t_token_node	*current_token;
// 	int				word_count;

// 	exec_list = NULL;
// 	last_exec_node = NULL;
// 	current_token = *token_list;
// 	word_count = 0;
// 	while (current_token != NULL)
// 	{
// 		if (current_token->type == TOKEN_WORD)
// 			add_word_to_exec_word_node(&exec_list, current_token->value, &word_count, &last_exec_node);
// 		else if (current_token->type == TOKEN_REDIR_IN
// 				|| current_token->type == TOKEN_REDIR_OUT
// 				|| current_token->type == TOKEN_REDIR_APPEND
// 				|| current_token->type == TOKEN_REDIR_HEREDOC)
// 			add_exec_node_with_type(&exec_list, current_token->type, current_token->value);
// 		else if (current_token->type == TOKEN_PIPE)
// 		{
// 			add_exec_node_with_type(&exec_list, current_token->type, current_token->value);
// 			word_count = 0;
// 			last_exec_node = NULL;
// 		}
// 		current_token = current_token->next;
// 	}
// 	return (exec_list);
// }
