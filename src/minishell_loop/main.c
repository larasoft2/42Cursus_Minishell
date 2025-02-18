/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:58:59 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/18 11:29:39 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_input(char *input, int *syntax_status)
{
	if (syntax_error_checker(input) == EXIT_FAILURE)
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

int	tokenize_parsing(char *input, t_token_node **token_list, t_env **env_final, t_exec **exec_list)
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

void	minishell_loop(char *input, t_token_node **token_list, t_env **env_final, t_exec **exec_list)
{
	int	syntax_status;

	syntax_status = 0;
	add_history(input);
	if (check_syntax_input(input, &syntax_status) == EXIT_FAILURE)
		free(input);
	if (syntax_status == EXIT_SUCCESS)
		syntax_status = tokenize_parsing(input, token_list, env_final, exec_list);
	if (syntax_status == EXIT_SUCCESS && *input)
	{
		ft_process(env_final, *exec_list);
		free_exec_list(exec_list);
	}
}

void	check_ctrl_d(t_env **env, t_exec *exec_list)
{
	printf("exit\n");
	free_env_list(env);
	if (exec_list)
		free_exec_list(&exec_list);
	exit(EXIT_FAILURE);
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
	exec_list = NULL;
	env_final = get_env_list(env);
	setup_default_signals_handling();
	while (1)
	{
		setup_main_prompt_signals_handling();
		input = readline("minishell> ");
		if (!input)
			check_ctrl_d(&env_final, exec_list);
		minishell_loop(input, &token_list, &env_final, &exec_list);
		setup_default_signals_handling();
	}
	return (EXIT_SUCCESS);
}
