/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:21:59 by vharkush          #+#    #+#             */
/*   Updated: 2023/08/29 14:05:43 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_check_builtins(char **env, t_pipex *list)
// builins: cd echo env exit export pwd unset
{
    int builtin;

    builtin = 0;
    (void)env;
    if (!ft_strncmp(list->args[0], "env", 4))
       builtin += ft_env(list->data);
    if (builtin)
        list->args = NULL;
}