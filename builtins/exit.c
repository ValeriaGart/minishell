#include "../incl/minishell.h"

int	ft_exit_special_cond(t_pipex *list, t_tokens *toks, int i, int do_exit)
{
	if (do_exit)
	{
		ft_putstr_fd("exit\n", list->out);
		ft_error(toks->val, ": numeric argument required\n", 0);
		ft_list_loop_free(list, i);
		list->tokens = ft_free_toks(list->tokens);
		ft_list_free(list);
		rl_clear_history();
		ft_free_env(list->data->env, list->data);
		exit(2);
	}
	ft_putstr_fd("exit\n", list->out);
	ft_error(toks->val, ": too many arguments\n", 0);
	g_minishell = 1;
	return (1);
}

int	ft_long_exit_err(int n, t_tokens *toks)
{
	if (n > 20 || (n == 19 && toks->val[0] != '-' && toks->val[18] > '7') ||
		(n == 20 && toks->val[0] == '-' && toks->val[19] == '9')
		|| (n == 20 && toks->val[0] == '+' && toks->val[19] > '7'))
	{
		g_minishell = 2;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(toks->val, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (1);
	}
	return (0);
}

int	ft_exit_error_check(t_tokens *toks, int n, int i, t_pipex *list)
{
	int	rem;

	rem = n;
	if (toks->val[n] && (toks->val[n] == '-' || toks->val[n] == '+'))
		n++;
	while (toks->val[n] && ft_isdigit(toks->val[n]))
		n++;
	if (toks->val[n])
		ft_exit_special_cond(list, toks, i, 1);
	n = n - rem;
	if (!ft_long_exit_err(n, toks))
	{
		n = ft_atol(toks->val + rem);
		g_minishell = n % 256;
	}
	toks = toks->next;
	toks = ft_point_to_needed_tok(toks, i, 0, SEP);
	if (toks && toks->ind_command == i)
		return (ft_exit_special_cond(list, toks, i, 0));
	return (0);
}

void	ft_exit_p(t_pipex *list, t_tokens *toks, int i)
{
	toks = toks->next;
	(void)list;
	toks = ft_point_to_needed_tok(toks, i, 0, SEP);
	g_minishell = 0;
	if (toks && toks->ind_command == i)
	{
		if (ft_exit_error_check(toks, 0, i, list))
			return ;
	}
	ft_putstr_fd("exit\n", list->out);
	ft_list_loop_free(list, i);
	list->tokens = ft_free_toks(list->tokens);
	ft_list_free(list);
	rl_clear_history();
	ft_free_env(list->data->env, list->data);
	exit(g_minishell);
}
