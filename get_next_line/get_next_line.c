/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenng <yenng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:58:33 by vharkush          #+#    #+#             */
/*   Updated: 2023/08/02 11:53:46 by yenng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_if_newline(int i, char ***line)
{
	char	*ret;
	char	*temp;
	int		rem_i;

	rem_i = i + 1;
	ret = malloc(sizeof(char) * (i + 2));
	if (!ret)
		return (NULL);
	ret = ft_memcpy(ret, **line, i + 1);
	ret[i + 1] = '\0';
	i = ft_strlen(**line) - i;
	temp = malloc(sizeof(char) * i);
	if (!temp)
		return (NULL);
	temp[i - 1] = '\0';
	temp = ft_memcpy(temp, **line + rem_i, i - 1);
	free (**line);
	**line = ft_strdup(temp);
	free (temp);
	return (ret);
}

char	*ft_no_newline(int i, char ***line, int fd)
{
	char	*temp;
	char	*ret;

	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	i = read(fd, temp, BUFFER_SIZE);
	if (i < 0 || (i == 0 && **line[0] == 0))
	{
		free (**line);
		**line = NULL;
		free (temp);
		return (NULL);
	}
	temp[i] = '\0';
	ret = ft_strjoin(**line, temp);
	free (temp);
	free (**line);
	**line = NULL;
	if (i < BUFFER_SIZE && ft_int_strchr(ret, '\n') == -1)
		return (ret);
	**line = ft_strdup(ret);
	free (ret);
	return ("yo");
}

char	*ft_gimme_string(char **line, int fd)
{
	int		i;
	char	*ret;

	i = ft_int_strchr(*line, '\n');
	if (i >= 0)
		return (ft_if_newline(i, &line));
	else
	{
		ret = ft_no_newline(i, &line, fd);
		if (ret == NULL || *line == NULL)
			return (ret);
	}
	return (ft_gimme_string(line, fd));
}

char	*get_next_line(int fd, int freee)
{
	static char	*line;
	char		*ret;
	int			size;

	if (freee)
		free(line);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!line)
	{
		line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!line)
			return (NULL);
		size = read(fd, line, BUFFER_SIZE);
		if (size <= 0)
		{
			free (line);
			line = NULL;
			return (NULL);
		}
		line[size] = '\0';
	}
	ret = ft_gimme_string(&line, fd);
	return (ret);
}
