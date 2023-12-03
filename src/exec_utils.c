#include "../incl/minishell.h"

char	**ft_tok_to_args(t_tokens *toks, int i)
{
	int			y;
	char		**args;
	t_tokens	*rem_tok;

	y = 0;
	while (toks->ind_command != i)
		toks = toks->next;
	rem_tok = toks;
	while (toks && toks->ind_command == i)
	{
		if (toks->type != SEP)
			++y;
		toks = toks->next;
	}
	args = ft_calloc(sizeof(char *), y + 1);
	if (!args)
		return (0);
	i = -1;
	while (++i < y)
	{
		while (rem_tok->type == SEP)
			rem_tok = rem_tok->next;
		args[i] = rem_tok->val;
		rem_tok = rem_tok->next;
	}
	return (args);
}

char	*ft_gimme_com(char *str, t_pipex *list)
{
	char	*temp;
	char	*ret;
	char	**iter;

	iter = list->com_paths;
	while (*iter)
	{
		temp = ft_strjoin(*iter, "/");
		ret = ft_strjoin(temp, str);
		free(temp);
		if (access(ret, 0) == 0)
			return (ret);
		free(ret);
		iter++;
	}
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_minishell = 127;
	return (NULL);
}

char    **ft_env_to_twod_arr(t_env *env_list)
{
    char    **env_twod;
    int     i;
	t_env	*rem_env;

    i = -1;
	rem_env = env_list;
	while (rem_env)
	{
		rem_env = rem_env->next;
		i++;
	}
    env_twod = malloc(sizeof(char *) * (i + 1));
    if (!env_twod)
    {
        ft_error_msg("Malloc failed\n", 15);
        return (NULL);
    }
	i = -1;
    while (env_list->next)
    {
        env_twod[++i] = ft_strdup(env_list->str);
        if (!env_twod[i])
        {
            while (i >= 0)
                free(env_twod[--i]);
            free(env_twod);
            ft_error_msg("Malloc failed\n", 15);
            return (NULL);
        }
        env_list = env_list->next;
    }
    env_twod[++i] = NULL;
    return (env_twod);
}


void    ft_check_kid(int i, t_pipex *list)
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
		return;
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
		//dup2(1, STDOUT_FILENO);
 	}
}

char    *ft_bcheck_paths(t_env  *env)
{
    while (env->next)
    {
        if (!ft_strncmp("PATH", env->str, 4))
			return (env->str + 5);
        env = env->next;
    }
    ft_error_msg("Path not found in envs\n", 23);
    return (NULL);
}
