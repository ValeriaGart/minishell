

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "builtins.h"

extern int	minishell_global;

typedef struct s_cmd
{
	char			**comd;
	char			*comd_line;
	char			end_of_cmd;
	int				index;
	char			*check_input;
	int				i;
	int				j;
}					t_cmd;

typedef struct		s_dlist
{
	char			*str;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}					t_dlist;

typedef struct		s_tlist
{
	char			*comd;
	char			**flargs;
	char			*op;
	char			**env;
	char			*path;
	pid_t			pid;
	char			*doc;
	t_dlist			*prev;
	t_dlist			*next;
}					t_tlist;
// Valeria'part
typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}		t_env;

typedef struct s_data
{
	char		**comd;
	int			nbr_comd;
	int			in;
	int			out;
	int			err;
	t_env		*env;
	t_env		*env_orig;
}		t_data;

typedef struct s_pipex
{
	pid_t			*pids;
	int				n;
	int				file1;
	int				file2;
	int				**pipes;
	int				here_doc;
	char			**paths;
	char			*command;
	char			**com_paths;
	char			**args;
	t_data			*data;
}		t_pipex;

/* env.c */
int		ft_store_env(t_data *data, char **env_orig, char structt);
int		ft_free_env(t_env *env);
int		ft_env_init(t_data *data, char **env);

/* built ins */
int		ft_env(t_data *data, t_pipex *list);
int		ft_pwd(t_data *data, t_pipex *list);

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

/* exec.c */
void	ft_exec(char **env, int ac, char **av, t_data *data);

/* input.c */
int		ft_check_input(char	*read_cmd);
char	**create_path(t_dlist *c_path);

/* builtins.c */
void    ft_check_builtins(char **env, t_pipex *list);

// quote.c
int	are_quotes_closed(char *str);
int	handle_quote(char *str, int i);

//singal.c
void	get_sigint(int sig);

/* main.c */
int		ft_count_words(char **av);

#endif