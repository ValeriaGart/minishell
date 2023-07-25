/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:24:40 by vharkush          #+#    #+#             */
/*   Updated: 2023/07/25 19:29:13 by vharkush         ###   ########.fr       */
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
	int		in;
	int		out;
	int		exit;
	int		ret;
	int		err;
	t_env	*env;		
}		t_data;

#endif