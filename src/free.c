/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:12:49 by vharkush          #+#    #+#             */
/*   Updated: 2024/01/30 13:12:59 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void ft_list_loop_free(t_pipex *list, int i, int pipe_err)
{
	if (list->here_doc)
	{
		list->here_doc = 0;
		unlink(".heredoc");
	}
	if (list->command)
		free(list->command);
	list->command = NULL;
	if (list->redir_out != -1)
		close(list->redir_out);
	if (list->redir_in != -1)
		close(list->redir_in);
	list->args = ft_free_command(list->args);
	if (list->rem_fd != -1)
		close(list->rem_fd);
	if (i < list->ac - 1)
		list->rem_fd = list->pipes[0];
	if (list->ac != 1 && pipe_err == 0)
		close(list->pipes[1]);
	dup2(0, STDIN_FILENO);
	dup2(1, STDOUT_FILENO);
	dup2(2, STDERR_FILENO);
}

void ft_free_av(char **av)
{
	int i;

	i = 0;
	while (av && av[i])
	{
		free(av[i]);
		i++;
	}
	if (av)
		free(av);
}

void *save_free(void *s1, void *s2)
{
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
	return (NULL);
}

char *ft_strjoin_free(char const *s1, char const *s2)
{
	char *new;
	int i;
	int j;

	if (s2[0] == '\0')
		return (free((char *)s2), (char *)s1);
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new)
	{
		i = -1;
		while (s1[++i] != '\0')
			new[i] = s1[i];
		j = -1;
		while (s2[++j] != '\0')
			new[i + j] = s2[j];
		new[i + j] = '\0';
	}
	save_free((void *)s1, (void *)s2);
	return (new);
}

void *ft_free_array(char **array)
{
	int i;

	i = 0;
	if (!array)
		return (NULL);
	while (array[i])
	{
		save_free((void *)array[i], NULL);
		i++;
	}
	free(array);
	array = NULL;
	return (NULL);
}
