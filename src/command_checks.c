#include "../incl/minishell.h"

bool	ft_access_command(t_pipex *list, t_tokens *toks)
{
	if (access(list->command, F_OK) != 0)
	{
		if (ft_strrchr(toks->val, '/'))
			ft_error(toks->val, ": No such file or directory\n", 0);
		else
			ft_error(toks->val, ": command not found\n", 0);
		g_minishell = 127;
		return (false);
	}
	if (!list->paths_exist && !ft_strrchr(toks->val, '/'))
	{
		ft_error(toks->val, ": command not found\n", 0);
		g_minishell = 127;
		return (false);
	}
	return (true);
}

bool	ft_command_check(t_pipex *list, t_tokens *toks, int i)
{
	struct stat	buf;

	while (toks->ind_command != i)
		toks = toks->next;
	while (toks->type != COM)
		toks = toks->next;
	if (stat(list->command, &buf) == 0 && ft_strrchr(toks->val, '/'))
	{
		if (((buf.st_mode & S_IXUSR) == 0))
		{
			ft_error(toks->val, ": Permission denied\n", ft_strlen(toks->val));
			g_minishell = 126;
			return (false);
		}
		if (S_ISDIR(buf.st_mode))
		{
			ft_error(toks->val, ": Is a directory\n", 0);
			g_minishell = 126;
			return (false);
		}
	}
	if (ft_access_command(list, toks) == false)
		return (false);
	return (true);
}

char	**ft_tok_to_args(t_tokens *toks, int i, int y)
{
	char		**args;
	t_tokens	*rem_tok;

	toks = ft_point_to_needed_tok(toks, i, 0, 0);
	rem_tok = toks;
	while (toks && toks->ind_command == i)
	{
		if (toks->type != SEP)
			++y;
		toks = toks->next;
	}
	args = ft_calloc(sizeof(char *), y + 1);
	if (!args)
		return (NULL);
	i = -1;
	while (++i < y)
	{
		while (rem_tok->type == SEP)
			rem_tok = rem_tok->next;
		args[i] = ft_strdup(rem_tok->val);
		if (!args[i])
			return (ft_free_command(args));
		rem_tok = rem_tok->next;
	}
	return (args);
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
