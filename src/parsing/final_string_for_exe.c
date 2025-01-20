/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_string_for_exe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:30:59 by racoutte          #+#    #+#             */
/*   Updated: 2025/01/20 21:38:13 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_struct_exec(t_exec **exec_list)
{
	*exec_list = (t_exec *)malloc(sizeof(t_exec));
	if (!(*exec_list))
	{
		ft_putstr_fd("Error: malloc failed\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_memset(*exec_list, 0, sizeof(t_exec));
	(*exec_list)->fd_in = STDIN_FILENO;
	(*exec_list)->fd_out = STDOUT_FILENO;
	return (EXIT_SUCCESS);
}

void	init_exec_node(t_exec *new_node, t_token_type type, char *value)
{
	new_node->type = type;
	new_node->arg = (char **)ft_calloc(MAX_ARGS, sizeof(char *));
	if (!new_node->arg)
	{
		ft_putstr_fd("Error: malloc failed\n", STDERR_FILENO);
		free(new_node);
		return;
	}
	new_node->arg[0] = ft_strdup(value);
	if (!new_node->arg[0])
	{
		ft_putstr_fd("Error: strdup failed\n", STDERR_FILENO);
		free(new_node->arg);
		free(new_node);
		return;
	}
	new_node->fd_in = STDIN_FILENO;
	new_node->fd_out = STDOUT_FILENO;
	new_node->next = NULL;
}

t_exec	*add_exec_node_with_type(t_exec **exec_list, t_token_type type, char *value)
{
	t_exec	*new_node;
	t_exec	*temp;

	temp = *exec_list;
	new_node = (t_exec *)ft_calloc(1, sizeof(t_exec));
	if (!new_node)
	{
		ft_putstr_fd("Error: malloc failed\n", STDERR_FILENO);
		return (NULL);
	}
	init_exec_node(new_node, type, value);
	if (!new_node->arg)
		return (NULL);
	if (*exec_list == NULL)
		*exec_list = new_node;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
	return (new_node);
}

void	add_word(char **arg, char *value, int i)
{
	if (i >= MAX_ARGS - 1)
	{
		ft_putstr_fd("Error: too many arguments\n", STDERR_FILENO);
		return ;
	}
	arg[i] = ft_strdup(value);
	if (!arg[i])
	{
		ft_putstr_fd("Error: malloc failed\n", STDERR_FILENO);
		return ;
	}
	arg[i + 1] = NULL;
}

t_exec	*add_word_to_exec_word_node(t_exec **exec_list, char *value, int *word_count)
{
	t_exec	*temp;

	temp = *exec_list;
	if (*exec_list == NULL)
	{
		add_exec_node_with_type(exec_list, TOKEN_WORD, value);
		*word_count = 1;  // On initialise le compteur de mots à 1
		return (*exec_list);
	}
	// while (temp->next)
	// 	temp = temp->next;
	// if (temp->type == TOKEN_WORD)
	// {
		add_word(temp->arg, value, *word_count);
		(*word_count)++;
	//}
	// else if (temp->type == TOKEN_PIPE)
	// {
	// 	add_exec_node_with_type(exec_list, TOKEN_WORD, value);
	// 	*word_count = 1;  // On réinitialise le compteur de mots
	// }
	return (*exec_list);
}

t_exec	*add_all_tokens(t_token_node **token_list)
{
	t_exec			*exec_list;
	t_token_node	*current_token;
	int				word_count;

	exec_list = NULL;
	current_token = *token_list;
	word_count = 0;
	while (current_token != NULL)
	{
		if (current_token->type == TOKEN_WORD) // all TOKEN_WORD into a single node = CMD with OPTIONS
		{
			add_word_to_exec_word_node(&exec_list, current_token->value, &word_count);

		}
		else if (current_token->type == TOKEN_REDIR_IN
				|| current_token->type == TOKEN_REDIR_OUT
				|| current_token->type == TOKEN_REDIR_APPEND
				|| current_token->type == TOKEN_REDIR_HEREDOC)
		{
			add_exec_node_with_type(&exec_list, current_token->type, current_token->value);
		}
		else if (current_token->type == TOKEN_PIPE)
		{
			add_exec_node_with_type(&exec_list, current_token->type, current_token->value);
			word_count = 0;
		}
		current_token = current_token->next;
	}
	return (exec_list);
}

