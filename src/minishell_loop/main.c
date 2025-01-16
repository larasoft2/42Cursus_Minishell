/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:58:59 by racoutte          #+#    #+#             */
/*   Updated: 2025/01/16 13:50:43 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(char *input, t_token_node **token_list, char **env)
{
	t_env	*env_final;

	env_final = NULL;
	if (syntax_error_checker(input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*token_list = tokenize_input(input);
	if (token_list == NULL)
		return (EXIT_FAILURE);
	env_final = get_env_list(env);
	*token_list = clean_tokens(token_list, &env_final);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	char			*input;
	t_token_node	*token_list;

	input = NULL;
	token_list = NULL;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			ft_printf("exit\n");
			break ;
		}
		if (parsing(input, &token_list, env) == EXIT_FAILURE)
		{
			free(input);
			continue ;
		}
		if (*input)
			add_history(input);
		print_tokens(token_list);
		free(input);
		//free_token_list(token_list);
	}
	return (EXIT_SUCCESS);
}
