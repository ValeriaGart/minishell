/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynguyen <ynguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:13:38 by vharkush          #+#    #+#             */
/*   Updated: 2024/01/30 19:34:49 by ynguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

volatile	int		g_minishell;

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

bool	part_loop_shell(t_data *data, char **read_cmd, t_tokens *toks, int err)
{
	*read_cmd = ft_expander(*read_cmd, data);
	if (!(*read_cmd))
		return (false);
	if (check_input(*read_cmd, data) != 0)
		err = 1;
	if (*read_cmd[0] != '\0' && !err)
	{
		if (ft_pre_work(&toks, &err, *read_cmd) == false)
			err = -1;
	}
	else
	{
		free(*read_cmd);
		return (true);
	}
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
		sig_handel(1, data);
		//if (!read_cmd)
		//	read_cmd = readline("minishell: ");
		if (!read_cmd && isatty(STDIN_FILENO))
			read_cmd = readline("minishell: ");
		else if (!read_cmd)
		{
			char	*line;
			line = get_next_line(STDIN_FILENO, 0);
			if (!line)
				break ;
			read_cmd = ft_strtrim(line, "\n");
			free(line);
		}
		if (!read_cmd)
			break ;
		sig_handel(1, data);
		add_history(read_cmd);
		if (read_cmd[0] != '\0' && check_input(read_cmd, data) != 0)
			free(read_cmd);
		else if (read_cmd[0] != '\0')
			exec_success = part_loop_shell(data, &read_cmd, NULL, 0);
		read_cmd = NULL;
		if (exec_success != true)
			break ;
	}
	rl_clear_history();
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)av;
	data.exit_code = 0;
	if (ac > 1)
		return (0);
	if (ft_env_init(&data, env))
		return (1);
	ft_loop_minishell(&data);
	ft_free_env(data.env, &data);
	return (data.exit_code);
}
