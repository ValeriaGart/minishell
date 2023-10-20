
#include "../incl/minishell.h"

int		minishell_global;

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

void	ft_loop_minishell(char **env, t_data *data, char **av, int ac)
{
	char	*read_cmd;
	char	**input;

	read_cmd = NULL;
	(void)env;
	while (1)
	{
		if (!read_cmd)
			read_cmd = readline("minishell: ");
		if (!read_cmd)
			return ((void)printf("Unable to make prompt\n"));
		if (check_input(data, read_cmd) != 0)
			free(read_cmd); // free pls
		else
		{
			add_history(read_cmd);
			read_cmd = ft_expander(read_cmd, data);
			av = ft_split(read_cmd, '|');
			if (!av)
				printf("Unable to split commands and exec\n");
			ac = ft_count_words(av); // " added ac = "
			if (!ac)
				return ;
			input = malloc_input(av, ac);
			if (!input)
				return ;
			free(read_cmd);
			read_cmd = NULL;
			ft_exec(ac, av, data);
			// ft_pipex(env, av, ac);
			// free(av);
	  }
  }
	if (read_cmd)
   free(read_cmd);
  rl_clear_history();
}

int	main(int ac, char **av, char **env)
{
	t_data data;

	(void)av;
	signal(SIGINT, get_sigint);
	signal(SIGQUIT, SIG_IGN);
	if (ac > 1)
		return (0);
	if (ft_env_init(&data, env))
		return (1);
	ft_loop_minishell(env, &data, NULL, ac);
	ft_free_env(data.env);
	ft_free_env(data.env_orig);
	return (0);
}