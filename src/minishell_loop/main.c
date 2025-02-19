/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:58:59 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/19 16:58:14 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(char *input, t_token_node **token_list,
		t_env **env_final, t_exec **exec_list)
{
	int	syntax_status;

	syntax_status = 0;
	add_history(input);
	if (check_syntax_input(input, &syntax_status) == EXIT_FAILURE)
		free(input);
	if (syntax_status == EXIT_SUCCESS)
		syntax_status = tokenize_parsing(input, token_list, env_final,
				exec_list);
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
	char			*input;
	t_token_node	*token_list;
	t_env			*env_final;
	t_exec			*exec_list;

	(void)ac;
	(void)av;
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
