/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:15:09 by racoutte          #+#    #+#             */
/*   Updated: 2024/12/09 18:55:11 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// int	is_handled_special_character(char c)
// {
// 	if (c == '|' || c == '<' || c == '>')
// 		return (EXIT_SUCCESS);
// 	return (EXIT_FAILURE);
// }

// void add_token(t_token_node **list, t_token_node *new_token)
// {
// 	t_token_node *temp;

// 	if (!*list)
// 	{
// 		*list = new_token;
// 		return;
// 	}
// 	temp = *list;
// 	while (temp->next)
// 		temp = temp->next;
// 	temp->next = new_token;
// }

// t_token_node	**tokenize_input(char *input)
// {
// 	t_token_node	**token_list;
// 	int		i;

// 	token_list = NULL;
// 	i = 0;
// 	while (input[i])
// 	{
// 		if (ft_isspace(input[i]) == EXIT_FAILURE)
// 		{
// 			// a ajouter: creation new node t_token_node
// 			if (is_handled_special_character(input[i]) == EXIT_FAILURE) // remplissage du node si c'est un mot
// 			{
// 				while (is_handled_special_character(input[i]) == EXIT_FAILURE && input[i])
// 				{
// 					// ajouter input[i] au node
// 					i++;
// 				}
// 			}
// 			else // remplissage du node si c'est un special character
// 			{
// 				// ajouter input[i] au node
// 				if (input[i] == '|')
// 				{
// 					// ajouter au node le type TOKEN_PIPE
// 					// ajouter au node la valeur "|"
// 				}
// 				else if (input[i] == '<' && input[i + 1] != '<')
// 				{
// 					// ajouter au node le type TOKEN_REDIR_IN
// 					// ajouter au node la valeur "<"
// 				}
// 				else if (input[i] == '>' && input[i + 1] != '>')
// 				{
// 					// ajouter au node le type TOKEN_REDIR_OUT
// 					// ajouter au node la valeur ">"
// 				}
// 				else if (input[i] == '>' && input[i + 1] == '>')
// 				{
// 					// ajouter au node le type TOKEN_REDIR_APPEND
// 					// ajouter au node la valeur ">>"
// 				}
// 				else if (input[i] == '<' && input[i + 1] == '<')
// 				{
// 					// ajouter au node le type TOKEN_REDIR_HEREDOC
// 					// ajouter au node la valeur "<<"
// 				}
// 				i++;
// 			}
// 		}
// 		i++;
// 	}
// 	return (token_list_first);
// }