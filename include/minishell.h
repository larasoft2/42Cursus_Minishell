/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:59:18 by racoutte          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2024/12/02 12:09:22 by licohen          ###   ########.fr       */
=======
/*   Updated: 2024/12/02 12:09:22 by racoutte         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct token_type
{
	WORD;
	PIPE;
	REDIR;
}

typedef enum e_error
{
  
    ERR_QUOTE,          
    ERR_PIPE,
} t_error;



#endif