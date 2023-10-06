#include "minishell.h"

void	ft_change_args(t_pipex *list, int i)
{
	int		y;

	y = -1;
	while (list->args[i][++y])
		if (list->args[i][y] == '>' || list->args[i][y] == '<')
			break;
	if (y == 0)
		list->args[i] = NULL;
	else
	{
		list->args[i][y] = '\0';
		while (list->args[i][++y])
			list->args[i][y] = '\0';
	}
	if (list->args[++i])
	{
		list->args[i] = NULL;
		--(list->ac);
	}
}

void	ft_newinfd(t_pipex *list, char **args, int i)
{
	int		y;
	char	*file;

	y = -1;
	while (args[i][++y])
		if (args[i][y] == '<')
			break;
	if (args[i][y + 1] == '<')
	{
		list->redir_in = -3;
		return;
	}
	if (args[i][y + 1] != '\0')
		file = ft_strdup(args[i] + y + 1);
	else
		file = ft_strdup(args[i + 1]);
	list->redir_in = open(file, O_RDONLY);
	if (list->redir_in < 0)
		perror(file);
	ft_change_args(list, i);
	free(file);
}

void	ft_newoutfd(t_pipex *list, char **args, int i)
{
	int		y;
	char	*file;

	y = -1;
	while (args[i][++y])
		if (args[i][y] == '>')
			break;
	if (args[i][y + 1] == '>')
	{
		++y;
		list->redir_out = -3;
	}
	if (args[i][y + 1] != '\0')
		file = ft_strdup(args[i] + y + 1);
	else
		file = ft_strdup(args[i + 1]);
	if (list->redir_out == -3)
		list->redir_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0000644);
	else
		list->redir_out = open(file, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (list->redir_out < 0)
		perror(file);
	ft_change_args(list, i);
	free(file);
}

// wc -l <test>>new
void	ft_redirects(t_pipex *list, char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if (ft_strnstr(args[i], ">", ft_strlen(args[i])))
			ft_newoutfd(list, args, i);
		if (ft_strnstr(args[i], "<", ft_strlen(args[i])))
			ft_newinfd(list, args, i);
	}
}
