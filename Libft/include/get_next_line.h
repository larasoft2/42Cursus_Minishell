/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:59:12 by racoutte          #+#    #+#             */
/*   Updated: 2024/09/24 11:41:52 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
int		ft_find_c(char *str, char c);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t siz);
char	*ft_strcat_until_n(char *dest, char *src, char c);
char	*ft_strjoin_line_stash(char *s1, char const *s2, char c);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_read_until_newline(char *stash, char *line, int fd);
int		ft_read(int fd, char *stash, int nb_read);

#endif
