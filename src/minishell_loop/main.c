/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:58:59 by racoutte          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/12/19 15:20:08 by racoutte         ###   ########.fr       */
=======
/*   Updated: 2024/12/10 21:06:11 by lusavign         ###   ########.fr       */
>>>>>>> luna_exec
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(char *input, t_token_node **token_list)
{
	if (syntax_error_checker(input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*token_list = tokenize_input(input);
	if (token_list == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// char	*create_prompt(char *input)
// {

// }

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;

<<<<<<< HEAD
	char			*input;
	t_token_node	*token_list;
=======
	char *input;
>>>>>>> luna_exec

	input = NULL;
	token_list = NULL;
	while (1)
	{
		input = readline("minishell>$ ");
		if (!input)
		{
			ft_printf("exit\n");
			break ;
		}
		if (parsing(input, &token_list) == EXIT_FAILURE)
		{
			free(input);
			continue ;
		}
		if (*input)
			add_history(input);
		print_tokens(token_list);
		//ft_printf("\n", input);
		free(input);
		free_token_list(token_list);
	}
	return (EXIT_SUCCESS);
}
