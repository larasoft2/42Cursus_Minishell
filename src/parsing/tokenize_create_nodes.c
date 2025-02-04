/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_create_nodes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:56:02 by racoutte          #+#    #+#             */
/*   Updated: 2025/01/29 21:10:50 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipe_node(int *i, t_token_node **token_list)
{
	t_token_node	*pipe_node;
	t_token_type	type;
	char			*value;

	type = TOKEN_PIPE;
	value = ft_strdup("|");
	pipe_node = create_token_node(type, value);
	add_token(token_list, pipe_node);
	(*i)++;
	free(value);
}

void	create_redir_in_node(char *input, int *i, t_token_node **token_list)
{
	t_token_type	type;
	char			*value;

	type = TOKEN_REDIR_IN;
	(*i)++;
	skip_spaces(input, i);
	value = read_word(input, i);
	if (!value)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", STDERR_FILENO);
		return ;
	}
	add_token(token_list, create_token_node(type, value));
	free(value);
}

void	create_redir_out_node(char *input, int *i, t_token_node **token_list)
{
	t_token_type	type;
	char			*value;

	type = TOKEN_REDIR_OUT;
	(*i)++;
	skip_spaces(input, i);
	value = read_word(input, i);
	if (!value)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", STDERR_FILENO);
		return ;
	}
	add_token(token_list, create_token_node(type, value));
	free(value);
}

void	create_redir_append_node(char *input, int *i, t_token_node **token_list)
{
	t_token_type	type;
	char			*value;

	type = TOKEN_REDIR_APPEND;
	*i = *i + 2;
	skip_spaces(input, i);
	value = read_word(input, i);
	if (!value)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", STDERR_FILENO);
		return ;
	}
	add_token(token_list, create_token_node(type, value));
	free(value);
}

void	create_heredoc_node(char *input, int *i, t_token_node **token_list)
{
	t_token_type	type;
	char			*value;

	type = TOKEN_REDIR_HEREDOC;
	*i = *i + 2;
	skip_spaces(input, i);
	value = read_word(input, i);
	if (!value)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", STDERR_FILENO);
		return ;
	}
	add_token(token_list, create_token_node(type, value));
	free(value);
}
