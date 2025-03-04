/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:58:59 by racoutte          #+#    #+#             */
/*   Updated: 2025/03/04 13:48:13 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(char *input, t_token_node **token_list,
	t_env **env_final, t_exec **exec_list)
{
	int	syntax_status;

	syntax_status = 0;
	g_signal = 0;
	add_history(input);
	check_syntax_input(input, &syntax_status);
	if (syntax_status == EXIT_SUCCESS)
		syntax_status = tokenize_parsing(input, token_list, env_final,
				exec_list);
	if (syntax_status == EXIT_SUCCESS && *input)
	{
		//print_tokens_exec_list(*exec_list);
		ft_process(env_final, *exec_list);
		free_exec_list(exec_list);
	}
	free(input);
}

void	check_ctrl_d(t_env **env, t_exec *exec_list)
{
	printf("exit\n");
	free_env_list(env);
	if (exec_list)
		free_exec_list(&exec_list);
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env) //add condition if ac > 1, code shouldn't run
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
	env_final = NULL;
	if (ac > 1)
    {
        ft_putstr_fd("Wrong number of arguments\n", 2);
        return (EXIT_FAILURE);
    }
	env_final = set_env(env_final, env);
	setup_default_signals_handling();
	while (1)
	{
		setup_main_prompt_signals_handling();
		input = readline("minishell> ");
		if (!input)
			check_ctrl_d(&env_final, exec_list);
		minishell_loop(input, &token_list, &env_final, &exec_list);
		//print_tokens_exec_list(exec_list);
		setup_default_signals_handling();
	}
	return (EXIT_SUCCESS);
}
