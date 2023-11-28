#include "minishell.h"

// exit lol 4
void	ft_exit_p(t_tokens *toks, int  i)
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
	if (toks && minishell_global != 2)
		return ;
	exit(minishell_global);
}

void	ft_exit_error_check(t_tokens *toks, int n, int i)
{
	while (toks->val[n] && ft_isdigit(toks->val[n]))
		n++;
	if (toks->val[n])
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_error(toks->val, ": numeric argument required\n", 0);
		minishell_global = 2;
		exit(2);
	}
	if (toks && toks->ind_command == i)
		while (toks && toks->ind_command == i && toks->type == SEP)
			toks = toks->next;
	if (toks && toks->ind_command == i)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_error(toks->val, ": too many arguments\n", 0);
		minishell_global = 0;
		exit (0);
	}
}

void	ft_exit(t_tokens *toks, int i)
{
	int	n;

	toks = toks->next;
	n = 0;
	if (toks && toks->ind_command == i)
		while (toks && toks->ind_command == i && toks->type == SEP)
			toks = toks->next;
	if (toks && toks->ind_command == i)
		ft_exit_error_check(toks, n, i);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	minishell_global = 0;
	exit(minishell_global);
}
