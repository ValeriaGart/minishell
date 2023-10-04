
#include "../incl/minishell.h"

int ft_check_input(t_cmd *re)
{
    if (are_quotes_closed(re->check_input) == 1)
        return (1);
    return (0);
}

int ft_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (c);
	return (0);
}

void	handle_char(t_cmd *cmd, const char *line)
{
	if (ft_quote(line[cmd->i]) && cmd->end_of_cmd == '\0')
		cmd->end_of_cmd = line[cmd->i];
	else if (line[cmd->i] == cmd->end_of_cmd)
		cmd->end_of_cmd = '\0';
	else
		cmd->comd_line[(cmd->j)++] = line[(cmd->i)];
	(cmd->i)++;
}

/*
char	**create_path(t_dlist *c_path)
{
	char	*environ;
	char	**new;
	t_dlist	*create_path;

	create_path = c_path;
	new = NULL;
	while (c_path)
	{
		if (ft_strncmp(c_path->str, "PATH", 4) == 0)
		{
			environ = c_path->str;
			break ;
		}
		c_path = c_path->next;
	}
	if (c_path != NULL)
		new = ft_split(environ, ':');
	c_path = create_path;
	return (new);
}
int	check_operator(t_tlist *lis, t_data *vars)
{
	if (lis->comd != NULL && ft_strcmp(lis->comd, "exit") == 0)
	{
		ft_putstr_fd("exit\n", 1);
		if (lis->flargs != NULL && lis->flargs[0] != NULL)
			ft_free_and_exit(vars, ft_atoi(lis->flargs[0]));
		else
			ft_free_and_exit(vars, 0);
	}
	if (lis->op != NULL)
	{
		if (ft_strcmp(lis->op, "<") == 0)
			return (1);
	}
	if (lis->prev == NULL)
		return (0);
	if (lis->prev->op == NULL)
		return (0);
	if (ft_strcmp(lis->prev->op, ">") == 0)
		return (ft_replace(lis->comd, vars->in, NULL));
	else if (ft_strcmp(lis->prev->op, ">>") == 0)
		return (ft_add(lis, vars));
	return (0);
}

*/