#include "../incl/minishell.h"

void	ft_echo_env(t_env *env, char *str, int *i, int out)
{
	int		n;
	t_env	*to_print;

	*i = *i + 1;
	n = *i;
	while (str[n])
	{
		if (n == *i && (str[n] == '?' || str[n] == '0'))
		{
			if (str[n] == '0')
				ft_putstr_fd("minishell", out);
			else
				ft_putnbr_fd(g_minishell, out);
			*i = *i + 1;
			return;
		}
		if (!ft_isalpha(str[n]))
			break;
		n++;
	}
	if (n == *i)
		return ;
	to_print = ft_is_env(env, str + *i, n - *i);
	if (to_print)
		ft_putstr_fd(to_print->str, out);
	*i = n;
}

int		ft_error_screen(char *str)
 {
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '!' && str[i + 1])
			return (ft_error(str, ": event not found\n",  i));
		i++;
	}
	return (0);
}

int		ft_echo_normal(t_env *env, char *str, int out)
{
	int	i;
	int	meet_again;

	i = 0;
	meet_again = 0;
	(void)env;
	if (ft_error_screen(str))
		return (1);
	while (str[i])
	{
		if (str[i] == D || str[i] == S)
		{
			if (!meet_again)
				meet_again = str[i];
			else
				meet_again = 0;
		}
		if (meet_again == S)
		{
			while(str[++i] != S)
				write(out, &str[i], 1);
			i++;
			meet_again = 0;
		}
		else if (str[i] == D)
			i++;
		else
		{
			if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) == 1 || str[i + 1] == '?'))
				break;
			write(out, &str[i], 1);
			i++;
		}
	}
	if (str[i])
		ft_echo_env(env, str, &i, out);
	if (str[i])
		ft_echo_normal(env, str + i, out);
	return (0);
}

int		ft_echo(t_pipex *list, t_tokens *toks, int i)
{
	int	out;
	int	err;

	out = 1;
	err = 0;
	if (list->redir_out != -1)
		out = list->redir_out;
	while (toks->ind_command != i)
		toks = toks->next;
	toks = toks->next;
	while (toks && toks->ind_command == i && toks->type == SEP)
		toks = toks->next;
	if (toks && toks->ind_command == i && toks->type == COM)
	{
		while (toks && toks->ind_command == i)
		{
			err = ft_echo_normal(list->data->env, toks->val, out);
			toks = toks->next;
		}
	}
	if (!err)
		write(1, "\n", out);
	return (0);
}