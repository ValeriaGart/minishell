/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:24:40 by vharkush          #+#    #+#             */
/*   Updated: 2023/07/28 12:43:54 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "../libft/libft.h"

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}		t_env;

typedef struct s_data
{
	int			in;
	int			out;
	int			err;
	t_env		*env;
	t_env		*env_orig;
}		t_data;

/* env.c */
int		ft_store_env(t_data *data, char **env_orig, char structt);
int		ft_free_env(t_env *env);
int		ft_env_init(t_data *data, char **env);

/* built ins */
void	ft_env(t_data data);
int		ft_pwd(t_data data);

#endif