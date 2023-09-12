

#include "minishell.h"

void	ft_print_error(int	builtin, char *cmd, t_pipex *list)
/*
-1: failed malloc
-2: too many args env
-3: too many args pwd 
=======
-3: too many args pwd
*/
{
	printf("%s: ", cmd);
	if (builtin == -1)
		printf("malloc failed\n");
	if (builtin == -2)
		printf("'%s': No such file or directory\n", list->args[1]);
	if (builtin == -3)
		printf("too many arguments\n");
}

void    ft_check_builtins(char **env, t_pipex *list)
// builins: cd echo env exit export pwd unset
{
    int builtin;

    builtin = ft_strlen(list->args[0]);
    (void)env;
    if (builtin >= 3 && !ft_strncmp(list->args[0], "env", 4))
       builtin = ft_env(list->data, list);
	if (builtin >= 2 && !ft_strncmp(list->args[0], "cd", 3))
       builtin = 0;
	if (builtin >= 4 && !ft_strncmp(list->args[0], "exit", 5))
       builtin = 0;
	if (builtin >= 6 && !ft_strncmp(list->args[0], "export", 7))
       builtin = 0;
	if (builtin >= 5 && !ft_strncmp(list->args[0], "unset", 6))
       builtin = 0;
	if (builtin >= 4 && !ft_strncmp(list->args[0], "echo", 5))
       builtin = 0;
	if (builtin >= 3 && !ft_strncmp(list->args[0], "pwd", 4))
       builtin = ft_pwd(list->data, list);
	if (builtin < 0)
		ft_print_error(builtin, list->args[0], list);
    if (builtin <= 0)
        list->args = NULL;
}
