/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:58:59 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/14 12:04:26 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(char *input, t_token_node **token_list, t_env **env_final, t_exec **exec_list)
{
	if (syntax_error_checker(input) == EXIT_FAILURE)
	{
		modify_value_exit_code(2);
		return (EXIT_FAILURE);
	}
	*token_list = tokenize_input(input);
	if (*token_list == NULL)
		return (EXIT_FAILURE);
	*token_list = clean_tokens(token_list, env_final);
	if (init_struct_exec(*exec_list) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*exec_list = add_all_tokens(token_list);
	if (!exec_list)
		return (EXIT_FAILURE);
	// free_token_list(token_list);
	// print_tokens_exec_list(exec_list);
	ft_process(env_final, *exec_list);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	char			*input;
	t_token_node	*token_list;
	t_env			*env_final;
	t_exec			*exec_list;

	input = NULL;
	token_list = NULL;
	env_final = get_env_list(env);
	handle_signals(0, 0);
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (parsing(input, &token_list, &env_final, &exec_list) == EXIT_FAILURE)
		{
			free(input);
			free_token_list(&token_list);
			free_exec_list(&exec_list);
			continue ;
		}
		if (*input)
			add_history(input);
		free(input);
		//free_routine_all_lists(&token_list, &env_final, &exec_list);
	}
	// free liste env;
	return (EXIT_SUCCESS);
}
