/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenng <yenng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:21:59 by vharkush          #+#    #+#             */
/*   Updated: 2023/08/05 13:57:53 by yenng            ###   ########.fr       */
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

void	ft_loop_minishell(char **env, t_data *data, char **av, int ac)
{
	int	i;
	(void)data;
	char *read_cmd;

	i = 0;
	read_cmd = NULL;
	while(1)
	{
		if (!read_cmd)
			read_cmd = readline("minishell:§ ");
		if (!read_cmd)
			printf("Unable to make prompt\n");
		av = ft_split(read_cmd, ' ');
		if (!av)
			printf("Unable to split command\n");
		ft_count_words(av);
		while (i < ac)
		{
			printf("av[%d]: %s\n", i, av[i]);
			i++;
		}
		printf("ac: %d , %s\n", ac, av[1]);
		ft_pipex(env, av, ac);
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
