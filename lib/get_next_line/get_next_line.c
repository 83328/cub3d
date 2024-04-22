/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 22:43:58 by alimpens          #+#    #+#             */
/*   Updated: 2023/01/17 13:41:41 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*freetogo(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if ((stash && !ft_strchr(stash, '\n')) || !stash)
		stash = ft_read_and_stash(fd, stash);
	if (!stash)
	{
		stash = NULL;
		return (NULL);
	}
	line = ft_get_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		line = NULL;
		return (NULL);
	}
	stash = ft_cleanup(stash);
	if (!stash)
		freetogo(&stash);
	return (line);
}

char	*ft_get_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] && stash[i] == '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_cleanup(char *stash)
{
	int		i;
	int		c;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		new_stash = NULL;
		freetogo(&stash);
		return (NULL);
	}
	new_stash = (char *)malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!new_stash)
		return (NULL);
	i++;
	c = 0;
	while (stash[i])
		new_stash[c++] = stash[i++];
	new_stash[c] = '\0';
	freetogo(&stash);
	return (new_stash);
}

char	*ft_read_and_stash(int fd, char *stash)
{
	char	*buff;
	int		read_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(stash, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			freetogo(&buff);
			freetogo(&stash);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		stash = ft_strjoin(stash, buff);
	}
	freetogo(&buff);
	return (stash);
}
/* 
#include "get_next_line_bonus.h"
#include <fcntl.h> // for using open

int main()
{

	int fd = open("hello.txt", O_RDONLY);
	char *str = get_next_line(fd);
	
	fd = 45544;
	
	while (str)
	{
		printf("-->%s<--", str);
		//free(str);
		str = get_next_line(fd);
	}
	close(fd);
	//free(str);
	return (0);
}
*/