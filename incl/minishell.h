
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
# define PIPE "|"

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
	int			exit_st;
	t_env		*env;
	t_env		*env_orig;
}		t_data;

typedef struct s_pipex
{
	pid_t			*pids;
	int				ac;
	int				redir_in;
	int				redir_out;
	int				rem_fd;
	int				pipes[2];
	int				here_doc;
	char			*paths;
	char			*command;
	char			**args;
	char			**com_paths;
	char			**valid_env;
	t_data			*data;
}		t_pipex;

/* env.c */
int		ft_store_env(t_data *data, char **env_orig, char structt);
int		ft_free_env(t_env *env);
int		ft_env_init(t_data *data, char **env);

/* built ins */
int		ft_env(t_data *data, t_pipex *list);
int		ft_pwd(t_data *data, t_pipex *list);

/* exec.c */
int		ft_exec(int ac, char **av, t_data *data);

/* exec_utils.c */
char    *ft_bcheck_paths(t_data *data, t_env  *env);
char    **ft_env_to_twod_arr(t_data *data, t_env *env_list);
void    ft_check_kid(int i, t_pipex *list);
char	*ft_gimme_com(char *command, t_pipex *list);

/* utils.c */
int		ft_error_msg(t_data *data, char *msg, int msg_len);
void	ft_list_free(t_pipex *list);

/* redirects.c */
void	ft_redirects(t_pipex *list, char **args);

/* input.c */
int		ft_check_input(t_cmd *re);
char	**create_path(t_dlist *c_path);

/* builtins.c */
void    ft_check_builtins(char **env, t_pipex *list);

// quote.c
int	are_quotes_closed(char *str);
int	handle_quote(char *str, int i);

//quote_utils.c
int	count_index(char *str, int last_inx);

//singal.c
void	get_sigint(int sig);

/* main.c */
int		ft_count_words(char **av);

/* builtins.c */
void    ft_check_builtins(char **env, t_pipex *list);

/* main.c */
int		ft_count_words(char **av);

/* signal.c */
void	get_sigint(int sig);

#endif