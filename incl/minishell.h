
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# define PIPE 124
# define D 34
# define S 39

extern int			minishell_global;

typedef struct s_dlist
{
	char			*str;
	int				quote;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}					t_dlist;

typedef struct s_tlist
{
	char			*comd;
	char			**flargs;
	char			*op;
	char			**env;
	char			**path;
	pid_t			pid;
	char			*doc;
	struct s_tlist	*prev;
	struct s_tlist	*next;
}					t_tlist;

// Valeria'part
typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}		t_env;

typedef struct s_data
{
	char			**comd;
	char			*comd_line;
	char			end_of_cmd;
	int				index;
	char			*check_input;
	int				i;
	int				j;
	int				at;
	int				exit;
	pid_t			*pid;
	int				out;
	// valeria's
	int				exit_st;
	t_env			*env;
	t_env			*env_orig;
}					t_data;

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
}					t_pipex;


/* env.c */
int					ft_store_env(t_data *data, char **env_orig, char structt);
int					ft_free_env(t_env *env);
int					ft_env_init(t_data *data, char **env);

/* built ins */
int					ft_env(t_data *data, t_pipex *list);
int					ft_pwd(t_data *data, t_pipex *list);

// free.c
int					free_n_exit(t_data *d, int i);

// input_check.c
int					syntax_errors(t_data *d, char c);
int					check_input(t_data *d, char *s);

// input_utils.c
int					ft_strcmp(char *s1, char *s2);

/* exec.c */
int					ft_exec(int ac, char **av, t_data *data);

/* utils.c */
int		ft_error_msg(t_data *data, char *msg, int msg_len);
void	ft_list_free(t_pipex *list);

/* redirects.c */
void	ft_redirects(t_pipex *list, char **args);

/* builtins.c */
void				ft_check_builtins(char **env, t_pipex *list);

// quote.c
int					ft_is_space(char s, int space);
int					quote_error_message(void);
int					check_open_quote(t_data *d, char *s);

// singal.c
void				get_sigint(int sig);

/* main.c */
int					ft_count_words(char **av);

// token.c
t_dlist				*ft_create_dlist(char *s, int quote);
void				ft_add_dlist_back(t_dlist **dl, char *str, int quote);
void				ft_token_loop(char *s, int *q, int *i, int **sum_q);

#endif