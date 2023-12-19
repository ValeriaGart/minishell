#include "../incl/minishell.h"

int	ft_check_if_path(char *str)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (str[i] && str[i] == '/')
			break ;
		else if (str[i] && str[i] != '.')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_gimme_com(t_tokens *toks, t_pipex *list, int i)
{
	char	*temp;
	char	*ret;
	char	**iter;

	while (toks && !(toks->ind_command == i && toks->type == COM))
		toks = toks->next;
	if (!toks)
		return (NULL);
	iter = list->com_paths;
	while (*iter)
	{
		temp = ft_strjoin(*iter, "/");
		ret = ft_strjoin(temp, toks->val);
		free(temp);
		if (access(ret, 0) == 0)
			return (ret);
		free(ret);
		iter++;
	}
	list->paths_exist = 0;
	ret = ft_strdup(toks->val);
	return (ret);
}

int	ft_right_out(t_pipex *list, int i)
{
	if (list->redir_out > 0)
		return (list->redir_out);
	if (list->ac == 1)
		return (1);
	if (i == 0)
		return (list->pipes[1]);
	else if (i != list->ac - 1 && i != 0)
		return (list->pipes[1]);
	return (1);
}

void	ft_check_kid(int i, t_pipex *list)
{
	if (list->redir_out > 0)
	{
		dup2(list->redir_out, STDOUT_FILENO);
		close(list->redir_out);
	}
	if (list->redir_in > 0)
	{
		dup2(list->redir_in, STDIN_FILENO);
		close(list->redir_in);
	}
	if (list->ac == 1)
		return ;
	if (i == 0)
	{
		if (list->redir_out < 0)
			dup2(list->pipes[1], STDOUT_FILENO);
		close(list->pipes[1]);
		close(list->pipes[0]);
	}
	else if (i != list->ac - 1 && i != 0)
	{
		if (list->redir_out < 0)
			dup2(list->pipes[1], STDOUT_FILENO);
		if (list->redir_in < 0)
			dup2(list->rem_fd, STDIN_FILENO);
		close(list->rem_fd);
		close(list->pipes[0]);
		close(list->pipes[1]);
	}
	else
	{
		if (list->redir_in < 0)
			dup2(list->rem_fd, STDIN_FILENO);
		close(list->rem_fd);
	}
}

char	*ft_bcheck_paths(t_env	*env)
{
	while (env->next)
	{
		if (!ft_strncmp("PATH", env->str, 4))
			return (env->str + 5);
		env = env->next;
	}
	return (NULL);
}
