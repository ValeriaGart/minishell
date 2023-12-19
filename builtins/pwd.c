#include "minishell.h"

int	ft_pwd(t_pipex *list)
{
	char	*pwd;
	char	*tmp;
	int		out;

	out = 1;
	out = list->out;
	tmp = ft_calloc(sizeof(char), 10000);
	if (tmp == NULL)
		return (1);
	pwd = getcwd(tmp, 9999);
	if (pwd == NULL)
		return (1);
	ft_putendl_fd(pwd, out);
	free (pwd);
	return (0);
}
