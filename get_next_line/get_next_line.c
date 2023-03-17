/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:29:32 by ymehlil           #+#    #+#             */
/*   Updated: 2023/01/25 18:48:59 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *stash)
{
	int		n;
	char	*buf;

	n = 1;
	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (n != 0 && !ft_strchr1(stash, '\n'))
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n == -1)
			return (free(buf), NULL);
		buf[n] = 0;
		stash = ft_strjoin1(stash, buf);
	}
	free(buf);
	return (stash);
}

char	*ft_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = 0;
	return (line);
}

char	*ft_new_stash(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] && stash[i] == '\n')
		i++;
	new_stash = (char *)malloc(sizeof(char) * ft_strlen1(stash) - i + 1);
	if (!new_stash)
		return (NULL);
	j = 0;
	while (stash[i])
	{
		new_stash[j] = stash[i];
		j++;
		i++;
	}
	new_stash[j] = 0;
	if (new_stash[0] == 0)
		return (free(stash), free(new_stash), NULL);
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_line(stash);
	stash = ft_new_stash(stash);
	if (line[0] == 0)
	{
		free(stash);
		free(line);
		return (NULL);
	}
	return (line);
}
