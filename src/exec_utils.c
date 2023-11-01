#include "../incl/minishell.h"

char	*ft_gimme_com(char *command, t_pipex *list)
{
	char	*temp;
	char	*ret;
	char	**iter;

	if (!command)
		return (NULL);
	iter = list->com_paths;
	while (*iter)
	{
		temp = ft_strjoin(*iter, "/");
		ret = ft_strjoin(temp, command);
		free(temp);
		if (access(ret, 0) == 0)
			return (ret);
		free(ret);
		iter++;
	}
	return (NULL);
}

char    **ft_env_to_twod_arr(t_data *data, t_env *env_list)
{
    char    **env_twod;
    int     i;

    i = -1;
    env_twod = malloc(sizeof(char *));
    if (!env_twod)
    {
        ft_error_msg(data, "Malloc failed\n", 15);
        return (NULL);
    }
    while (env_list->next)
    {
        env_twod[++i] = ft_strdup(env_list->str);
        if (!env_twod[i])
        {
            while (i >= 0)
                free(env_twod[--i]);
            free(env_twod);
            ft_error_msg(data, "Malloc failed\n", 15);
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

char    *ft_bcheck_paths(t_data *data, t_env  *env)
{
    while (env->next)
    {
        if (!ft_strncmp("PATH", env->str, 4))
			return (env->str + 5);
        env = env->next;
    }
    ft_error_msg(data, "Path not found in envs\n", 23);
    return (NULL);
}
