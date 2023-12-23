#include "../incl/minishell.h"

int		g_minishell;

// if input i == -1 -> return ac
int	ft_find_tok(t_tokens *toks, int i)
{
	while (toks && toks->next)
		toks = toks->next;
	if (i == -1)
		return (toks->ind_command + 1);
	return (0);
}

bool	ft_pre_work(t_tokens **toks, int *err, char *read_cmd)
{
	char	**av;

	av = ft_command_split(read_cmd);
	if (!av)
		return (false);
	*toks = ft_gimme_tokens(av);
	av = ft_free_command(av);
	if (!*toks)
		*err = -1;
	return (true);
}

bool	part_loop_shell(t_data *data, char **read_cmd)
{
	t_tokens	*toks;
	int			err;

	err = 0;
	*read_cmd = ft_expander(*read_cmd, data);
	if (!(*read_cmd))
		return (false);
	toks = NULL;
	if (*read_cmd[0] != '\0')
	{
		if (ft_pre_work(&toks, &err, *read_cmd) == false)
			return (false);
	}
	else
		return (true);
	if (*read_cmd)
		free(*read_cmd);
	*read_cmd = NULL;
	if (!err && ft_find_tok(toks, -1))
		err = ft_exec(data, toks);
	if (err < 0)
		return (false);
	return (true);
}

void	ft_loop_minishell(t_data *data)
{
	char	*read_cmd;
	bool	exec_success;

	exec_success = 1;
	read_cmd = NULL;
	while (1)
	{
		sig_handel(1);
		if (!read_cmd)
			read_cmd = readline("minishell: ");
		if (!read_cmd)
			break ;
		add_history(read_cmd);
		if (read_cmd[0] != '\0' && check_input(read_cmd) != 0)
			;
		else if (read_cmd[0] != '\0')
			exec_success = part_loop_shell(data, &read_cmd);
		read_cmd = NULL;
		if (exec_success != true)
			break ;
	}
	rl_clear_history();
}

//TODO: check if signals work properly
//TODO: SHLVL only till 9, after that don't open any new shells
int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)av;
	if (ac > 1)
		return (0);
	if (ft_env_init(&data, env))
		return (1);
	ft_loop_minishell(&data);
	ft_free_env(data.env, &data);
	return (0);
}
