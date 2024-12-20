/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:24:09 by racoutte          #+#    #+#             */
/*   Updated: 2024/12/20 14:12:56 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_syntax_message(t_error error)
{
	if (error == SYNTAX_ERROR_REDIR_SINGLE_RIGHT)
		ft_putendl_fd("minishell: syntax error near unexpected token `>'", 2);
	else if (error == SYNTAX_ERROR_REDIR_DOUBLE_RIGHT)
		ft_putendl_fd("minishell: syntax error near unexpected token `>>'", 2);
	else if (error == SYNTAX_ERROR_REDIR_SINGLE_LEFT)
		ft_putendl_fd("minishell: syntax error near unexpected token `<'", 2);
	else if (error == SYNTAX_ERROR_REDIR_DOUBLE_LEFT)
		ft_putendl_fd("minishell: syntax error near unexpected token `<<'", 2);
	else if (error == SYNTAX_ERROR_PIPE_SINGLE)
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
	else if (error == SYNTAX_ERROR_NEWLINE)
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			2);
	else if (error == SYNTAX_ERROR_UNCLOSED_QUOTES)
		ft_putendl_fd("minishell: syntax error, unclosed quotes, not handled",
			2);
	else if (error == SYNTAX_ERROR_NOT_HANDLED)
		ft_putendl_fd("minishell: syntax error, not handled", 2);
}

void	print_error_not_handled(char c)
{
	ft_putstr_fd("minishell: syntax error, not handled character '", 2);
	if (c)
	{
		ft_putchar_fd(c, 2);
		ft_putendl_fd("'", 2);
	}
}

void	print_error_not_handled_word(char *word)
{
	ft_putstr_fd("minishell: syntax error, not handled character '", 2);
	if (word != NULL)
	{
		ft_putstr_fd(word, 2);
		ft_putendl_fd("'", 2);
	}
}

char	*get_error_exec_message(t_error error) // change to putend fd
{
	if (error == COMMAND_NOT_FOUND)
		return ("command not found");
	else if (error == NOT_A_VALID_IDENTIFIER)
		return ("not a valid identifier");
	else if (error == NO_SUCH_FILE_OR_DIRECTORY)
		return ("No such file or directory");
	else if (error == NUMERIC_ARGUMENT_REQUIRED)
		return ("numeric argument required");
	else if (error == INVALID_OPTION)
		return ("invalid option");
	else if (error == TOO_MANY_ARGUMENTS)
		return ("too many arguments");
	return (NULL);
}

void	print_error_exec_message(t_error error, char *word)
{
	ft_putstr_fd("minishell: ", 2);
	if (word != NULL)
		ft_putstr_fd(word, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(get_error_exec_message(error), 2);
}
