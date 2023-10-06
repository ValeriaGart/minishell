
#include "../incl/minishell.h"

t_dlist	*ft_create_dlist(char *s, int quote)
{
	t_dlist	*node;

	node = malloc(sizeof(t_dlist));
	if (!node)
		return (NULL);
	node->str = ft_strdup(s);
	node->quote = quote;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	ft_add_dlist_back(t_dlist **dl, char *str, int quote)
{
	t_dlist	*tmp;

	if (!*dl)
	{
		*dl = ft_create_dlist(str, quote);
		return ;
	}
	tmp = (*dl);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ft_create_dlist(str, quote);
	tmp->next->prev = tmp;
}

int	which_operator(char *s, int q)
{
	if (q != 0)
		return (0);
	if (ft_strncmp(s, ">>", 2) == 0)
		return (2);
	else if (ft_strncmp(s, "<<", 2) == 0)
		return (2);
	else if (ft_strncmp(s, "<", 1) == 0)
		return (1);
	else if (ft_strncmp(s, ">", 1) == 0)
		return (1);
	else if (ft_strncmp(s, PIPE, 1) == 0)
		return (1);
	else
		return (0);
}

/*
t_tlist	*ft_real_token(t_dlist *v, t_tlist *sing, t_data *j)
{
	t_tlist			*p;
	unsigned int	i;

	if (j->id == 1)
		sing = ft_create_tlist();
	p = sing;
	if (j->id == 2)
	{
		ft_add_tlist_back(&p);
		while (t->next != NULL)
			sing = sing->next;
	}
	i = 0;
	while (v != NULL)
		ft_real_token_loop(&v, &sing, &i, p);
	if (sing != NULL && sing->flargs != NULL)
		sing->flargs[i] = NULL;
	return (p);
}

void	ft_token_loop(char *s, int *q, int *i, int **sum_q)
{
	(*sum_q)[2] = 0;
	while (s[*i] && (ft_is_space(s[*i], *q) == 1) && get_operator(&s[*i],
			*q) == 0)
	{
		if ((*q == 0 && (s[*i] == S || s[*i] == D)) && (((*sum_q)[0] != 0
					&& s[*i] == D) || ((*sum_q)[1] != 0 && s[*i] == S)))
		{
			(*sum_q)[s[*i] % 2]--;
			*q = 1 + (s[*i] % 2);
		}
		else if ((*q == 2 && s[*i] == S) || (s[*i] == D && *q == 1))
		{
			(*sum_q)[2] = *q;
			*q = 0;
		}
		(*i)++;
	}
}

*/