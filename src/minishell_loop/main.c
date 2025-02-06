/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:58:59 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/06 18:37:52 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(char *input, t_token_node **token_list, t_env **env_final, t_exec **exec_list)
{
	// t_env	*env_final;
	// t_exec	*exec_list;

	// env_final = NULL;
	if (syntax_error_checker(input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*token_list = tokenize_input(input);
	if (*token_list == NULL)
		return (EXIT_FAILURE);
	// env_final = get_env_list(env);
	*token_list = clean_tokens(token_list, env_final);
	if (init_struct_exec(*exec_list) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*exec_list = add_all_tokens(token_list);
	if (!exec_list)
		return (EXIT_FAILURE);
	// free_token_list(token_list);
	// print_tokens_exec_list(exec_list);
	// printf("AVANT TOUT CONTROLE - UNSET pointeur ex->arg[1] =  %p\n", &exec_list->arg[1]);
	ft_process(env_final, *exec_list);
	//printf("\n");
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
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			ft_printf("exit\n");
			break ;
		}
		if (parsing(input, &token_list, &env_final, &exec_list) == EXIT_FAILURE)
		{
			free(input);
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
