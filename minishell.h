/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenng <yenng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:24:40 by vharkush          #+#    #+#             */
/*   Updated: 2023/08/04 14:19:38 by yenng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"

typedef struct s_pipex
{
	pid_t			*pids;
	int				n;
	int				file1;
	int				file2;
	int				**pipes;
	int				here_doc;
	char			*paths;
	char			*command;
	char			**com_paths;
	char			**args;
}		t_pipex;

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}		t_env;

typedef struct s_data
{
	char		comd[1024];
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

/* pipex_utils.c */
void	ft_bpfree(t_pipex *list, int i);
void	ft_unlink(t_pipex *list, char **av, int perror);
int		**ft_gimme_pipes(t_pipex *list, char **av);
void	free_pipes(int i, t_pipex *list, char **av, int exitt);
void	ft_check_child(int i, t_pipex *list);
char	*ft_bcheck_paths(char **envp);
void	perror_bmsg(char *error, int j, t_pipex *list, int i);
char	*ft_gimme_command(char *command, t_pipex *list);

/* pipex.c */
int		ft_pipex(char **env, char **av, int ac);

#endif