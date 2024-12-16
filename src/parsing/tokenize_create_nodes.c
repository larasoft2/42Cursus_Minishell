/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_create_nodes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:56:02 by racoutte          #+#    #+#             */
/*   Updated: 2024/12/13 11:46:05 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipe_node(char *input, int *i, t_token_node **token_list)
{
	t_token_node	*pipe_node;
	t_token_type	type;
	char			*value;

	type = TOKEN_PIPE;
	value = ft_strdup("|");
	pipe_node = create_token_node(type, value);
	add_token(token_list, pipe_node);
	*i += ft_strlen(value);
}

void	create_redir_in_node(char *input, int *i, t_token_node **token_list)
{
	t_token_type	type;
	char			*value;

	type = TOKEN_REDIR_IN;
	value = ft_strdup("<"); // la value doit etre egale au mot qui se trouve juste apres le symbole
	add_token(token_list, create_token_node(type, value));
	*i += ft_strlen(value);
}

void	create_redir_out_node(char *input, int *i, t_token_node **token_list)
{
	t_token_type	type;
	char			*value;

	type = TOKEN_REDIR_OUT;
	value = ft_strdup(">"); // la value doit etre egale au mot qui se trouve juste apres le symbole
	add_token(token_list, create_token_node(type, value));
	*i += ft_strlen(value);
}

void	create_redir_append_node(char *input, int *i, t_token_node **token_list)
{
	t_token_type	type;
	char			*value;

	type = TOKEN_REDIR_APPEND;
	value = ft_strdup(">>");
	add_token(token_list, create_token_node(type, value));
	*i += ft_strlen(value);
}

void	create_heredoc_node(char *input, int *i, t_token_node **token_list)
{
	t_token_type	type;
	char			*value;

	type = TOKEN_REDIR_HEREDOC;
	value = ft_strdup("<<");
	add_token(token_list, create_token_node(type, value));
	*i += ft_strlen(value);
}
