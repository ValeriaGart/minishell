
#include "../incl/minishell.h"

int		g_minishell;

int	ft_count_words(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
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

void    part_loop_shell(t_data *data, char **av, int ac, char *read_cmd)
{
	t_tokens	*toks;
    read_cmd = ft_expander(read_cmd, data);
    av = ft_command_split(read_cmd);
	if (!av)
		printf("Unable to split commands and exec\n");
	toks = ft_gimme_tokens(av);
    ac = ft_count_words(av);
    if (!ac)
        return ;
    free(read_cmd);
    read_cmd = NULL;
    ft_exec(ac, av, data, toks);
    ft_free_av(av);
}

void	ft_loop_minishell(char **env, t_data *data, char **av, int ac)
{
	char	*read_cmd;

	read_cmd = NULL;
	(void)env;
	while (1)
	{
		if (!read_cmd)
 			read_cmd = readline("minishell: ");
		if (!read_cmd)
			return ((void)printf("Unable to make prompt\n"));
		add_history(read_cmd);
		if (read_cmd[0] != '\0' && check_input(read_cmd) != 0)
			;
		else if (read_cmd[0] != '\0')
			part_loop_shell(data, av, ac, read_cmd);
		if (read_cmd)
		{
			free(read_cmd);
			read_cmd = NULL;
		}
	}
	rl_clear_history();
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)av;
	signal(SIGINT, get_sigint);
	signal(SIGQUIT, SIG_IGN);
	if (ac > 1)
		return (0);
	if (ft_env_init(&data, env))
		return (1);
	ft_loop_minishell(env, &data, NULL, ac);
	ft_free_env(data.env);
	if (data.pwd)
		free(data.pwd);
	return (0);
}
