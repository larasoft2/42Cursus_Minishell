/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:25:59 by racoutte          #+#    #+#             */
/*   Updated: 2024/09/24 11:36:54 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

int	ft_find_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_update_stash(char *stash)
{
	int	index;
	int	j;

	index = ft_find_c(stash, '\n');
	if (index == -1)
	{
		stash[0] = '\0';
		return (stash);
	}
	index++;
	j = 0;
	while (stash[index])
	{
		stash[j] = stash[index];
		index++;
		j++;
	}
	stash[j] = '\0';
	return (stash);
}

int	ft_read(int fd, char *stash, int nb_read)
{
	char	buffer[BUFFER_SIZE + 1];

	nb_read = read(fd, buffer, BUFFER_SIZE);
	if (nb_read < 0)
	{
		ft_memset(stash, 0, BUFFER_SIZE + 1);
		return (-1);
	}
	buffer[nb_read] = '\0';
	ft_strlcpy(stash, buffer, BUFFER_SIZE + 1);
	return (nb_read);
}

char	*ft_read_until_newline(char *stash, char *line, int fd)
{
	int	nb_read;

	nb_read = 1;
	while (nb_read > 0)
	{
		if (ft_find_c(stash, '\n') != -1)
		{
			line = ft_strjoin_line_stash(line, stash, '\n');
			ft_update_stash(stash);
			return (line);
		}
		else
		{
			line = ft_strjoin_line_stash(line, stash, '\0');
			nb_read = ft_read(fd, stash, nb_read);
			if (nb_read < 0)
				return (free(line), NULL);
		}
	}
	if (nb_read == 0)
	{
		line = ft_strjoin_line_stash(line, stash, '\0');
		stash[0] = '\0';
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*line;

	line = (char *)malloc(sizeof(char) * 1);
	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (free(line), NULL);
	line[0] = '\0';
	line = ft_read_until_newline(stash, line, fd);
	if (line && !*line)
		return (free(line), NULL);
	return (line);
}

// int	main(int ac, char **av)
// {
// 	(void)ac;

// 	char *line;
// 	int	fd = open(av[1], O_RDONLY);
// 	if (fd < 0)
// 		return (1);
// 	line = get_next_line(fd);
// 	while(line)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }
