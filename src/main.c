/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:21:59 by vharkush          #+#    #+#             */
/*   Updated: 2023/08/29 13:07:30 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_words(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

char	*ft_gimme_comm(char *command, char **paths)
{
	char	*temp;
	char	*ret;
	char	**iter;

	if (!command)
		return (NULL);
	iter = paths;
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

void	ft_execc(char **env, char **av)
{
	char	**args;
	char	*paths;
	char	*command;
	char	**com_paths;
	
	paths = ft_bcheck_paths(env);
	com_paths = ft_split(paths, ':');
	args = ft_split(av[1], ' ');
	command = ft_gimme_comm(args[0], com_paths);
	execve(command, args, env);
	free(args);
}

char	**malloc_input(char **av, int ac)
{
	char	**input;
	int		i;

	i = 1;
	input = NULL;
	input = ft_calloc(ac + 2, sizeof(char *));
	input[0] = malloc(12 * sizeof(char));
	input[0] = "./minishell\0";
	while (i <= ac)
	{
		input[i] = av[i - 1];
		i++;
	}
	input[i] = NULL;
	return (input);
}

void	ft_loop_minishell(char **env, t_data *data, char **av, int ac)
{
	(void)data;
	char	*read_cmd;
	char	**input;

	read_cmd = NULL;
	(void)env;
	while(1)
	{
	 	if (!read_cmd)
			read_cmd = readline("minishell:§ ");
		if (!read_cmd)
			printf("Unable to make prompt\n");
		if (ft_check_input(read_cmd))
			break;							//free pls
		av = ft_split(read_cmd, '|');
		if (!av)
			printf("Unable to split commands and exec\n");
		ac = ft_count_words(av); // " added ac = "
		if (!ac)
			return;
		input = malloc_input(av, ac);
		if (!input)
			return;
		free(read_cmd);
		read_cmd = NULL;
		ft_exec(env, ac, av, data);
		//ft_pipex(env, av, ac);
		//free(av);
	}
	if (read_cmd)
		free(read_cmd);
}

int	main(int ac, char **av, char**env)
{
	t_data	data;

	(void)av;
	if (ac > 1)
		return (0);
	data.in = 0;
	data.out = 1;
	data.err = 1;
	if (ft_env_init(&data, env))
		return (1);
	ft_loop_minishell(env, &data, NULL, ac);
	ft_free_env(data.env);
	ft_free_env(data.env_orig);
	return (0);
}
