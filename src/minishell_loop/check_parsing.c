/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:04:55 by racoutte          #+#    #+#             */
/*   Updated: 2025/03/04 13:48:04 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_input(char *input, int *syntax_status)
{
	if (syntax_error_checker_spaces_empty(input) == EXIT_FAILURE)
	{
		modify_value_exit_code(0);
		*syntax_status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	else if (syntax_error_checker(input) == EXIT_FAILURE)
	{
		modify_value_exit_code(2);
		*syntax_status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	*syntax_status = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}

int	parsing(char *input, t_token_node **token_list, t_env **env_final)
{
	*token_list = tokenize_input(input);
	if (*token_list == NULL)
		return (EXIT_FAILURE);
	*token_list = clean_tokens(token_list, env_final);
	return (EXIT_SUCCESS);
}

int	tokenize_parsing(char *input, t_token_node **token_list,
	t_env **env_final, t_exec **exec_list)
{
	if (parsing(input, token_list, env_final) == EXIT_FAILURE)
	{
		free(input);
		free_token_list(token_list);
		return (EXIT_FAILURE);
	}
	add_all_tokens(token_list, exec_list);
	free_token_list(token_list);
	return (EXIT_SUCCESS);
}
