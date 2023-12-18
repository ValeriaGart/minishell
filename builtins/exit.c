#include "../incl/minishell.h"

int	ft_exit_error_check(t_tokens *toks, int n, int i)
{
	int	rem;

	rem = n;
	if (toks->val[n] && (toks->val[n] == '-' || toks->val[n] == '+'))
		n++;
	while (toks->val[n] && ft_isdigit(toks->val[n]))
		n++;
	if (toks->val[n])
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_error(toks->val, ": numeric argument required\n", 0);
		g_minishell = 2;
		exit (g_minishell);
	}
	n = ft_atol(toks->val + rem);
	g_minishell = n % 256;
	toks = toks->next;
	if (toks && toks->ind_command == i)
		while (toks && toks->ind_command == i && toks->type == SEP)
			toks = toks->next;
	if (toks && toks->ind_command == i)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_error(toks->val, ": too many arguments\n", 0);
		g_minishell = 1;
		return (1);
	}
	return (0);
}

void	ft_exit_p(t_pipex *list, t_tokens *toks, int  i)
{
	toks = toks->next;
	(void)list;
	if (toks && toks->ind_command == i)
		while (toks && toks->ind_command == i && toks->type == SEP)
			toks = toks->next;
	g_minishell = 0;
	if (toks && toks->ind_command == i)
	{
		if (ft_exit_error_check(toks, 0, i))
			return;
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	ft_list_loop_free(list, i);
	list->tokens = ft_free_toks(list->tokens);
	ft_list_free(list);
	rl_clear_history();
	ft_free_env(list->data->env, list->data);
	exit(g_minishell);
}
