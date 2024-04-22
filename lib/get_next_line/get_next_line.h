/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 22:44:56 by alimpens          #+#    #+#             */
/*   Updated: 2023/01/04 16:42:36 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 23
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

size_t			ft_strlen(char const *str);
char			*ft_strchr(char *s, int c);
char			*ft_strjoin(char *s1, char *s2);
char			*get_next_line(int fd);
char			*ft_get_line(char *stash);
char			*ft_cleanup(char *stash);
char			*ft_read_and_stash(int fd, char *stash);
char			*freetogo(char **str);

#endif