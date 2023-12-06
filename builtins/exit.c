#include "../incl/minishell.h"

void	ft_exit_p(t_pipex *list, t_tokens *toks, int  i)
{
	toks = toks->next;
	if (toks)
		while (toks && toks->type == SEP)
			toks = toks->next;
	if (toks)
		toks = toks->next;
	if (toks)
		while (toks && toks->ind_command == i && toks->type == SEP)
			toks = toks->next;
	if (list->ac != 1 || (toks && g_minishell != 2))
		return ;
	exit(g_minishell);
}

//TODO: check atoi overflow
void	ft_exit_error_check(t_tokens *toks, int n, int i)
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
		exit(g_minishell);
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
		exit (g_minishell);
	}
}

//n%256
void	ft_exit(t_tokens *toks, int i)
{
	int	n;

	toks = toks->next;
	n = 0;
	if (toks && toks->ind_command == i)
		while (toks && toks->ind_command == i && toks->type == SEP)
			toks = toks->next;
	g_minishell = 0;
	if (toks && toks->ind_command == i)
		ft_exit_error_check(toks, n, i);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(g_minishell);
}
