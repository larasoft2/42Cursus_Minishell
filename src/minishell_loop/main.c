/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:58:59 by racoutte          #+#    #+#             */
/*   Updated: 2024/12/18 15:17:22 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;

	char			*input;
	t_token_node	*token_list;

	while (1)
	{
		input = readline("minishell>$ ");
		if (!input)
		{
			ft_printf("exit\n");
			break ;
		}
		if (syntax_error_checker(input) == EXIT_FAILURE)
		{
			free(input);
			continue ;
		}
		if (*input)
			add_history(input);
		ft_printf("input: %s\n", input);
		token_list = tokenize_input(input);
		print_tokens(token_list);
		ft_printf("\n\n", input);
		free(input);
		free_token_list(token_list);
	}
	return (EXIT_SUCCESS);
}
