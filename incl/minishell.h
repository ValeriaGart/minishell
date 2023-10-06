
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "builtins.h"
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
	char			*input;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	char			**comd;
	char			*comd_line;
	char			end_of_cmd;
	int				index;
	char			*check_input;
	int				i;
	int				j;
	int				exit;
	// valeria's
	int				nbr_comd;
	int				in;
	int				out;
	int				err;
	pid_t			*pid;
	char			*path;
	struct s_tlist	*start;
	struct s_dlist	*exp;
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
}		t_pipex;

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

/* pipex_utils.c */
void				ft_bpfree(t_pipex *list, int i);
void				ft_unlink(t_pipex *list, char **av, int perror);
int					**ft_gimme_pipes(t_pipex *list, char **av);
void				free_pipes(int i, t_pipex *list, char **av, int exitt);
void				ft_check_child(int i, t_pipex *list);
char				*ft_bcheck_paths(char **envp);
void				perror_bmsg(char *error, int j, t_pipex *list, int i);
char				*ft_gimme_command(char *command, t_pipex *list);

/* pipex.c */
int					ft_pipex(char **env, char **av, int ac);

/* exec.c */
int		ft_exec(int ac, char **av, t_data *data);

/* exec_utils.c */
char    *ft_bcheck_paths(t_data *data, t_env  *env);
char    **ft_env_to_twod_arr(t_data *data, t_env *env_list);
void    ft_check_kid(int i, t_pipex *list);
char	*ft_gimme_com(char *command, t_pipex *list);

/* builtins.c */
void				ft_check_builtins(char **env, t_pipex *list);

// quote.c
int					ft_is_space(char s, int space);
int					quote_error_message(void);
int					check_open_quote(t_data *d, char *s);

// quote_utils.c
/*
int					quote_exist(char *s);
int					ft_execute_symbols(char *str, int exc, int i);
int					index_in_quote(char *s, int inx);
void				no_quote_execute(char *s, int i, int j, int double_q);
int					quote_n_pipe(char *s, int inx, int start, int end);

*/

// singal.c
void				get_sigint(int sig);

/* main.c */
int					ft_count_words(char **av);

/* builtins.c */
void				ft_check_builtins(char **env, t_pipex *list);

/* main.c */
int					ft_count_words(char **av);

/* signal.c */
void				get_sigint(int sig);

// token.c
t_dlist				*ft_create_dlist(char *s, int quote);
void				ft_add_dlist_back(t_dlist **dl, char *str, int quote);
void				ft_token_loop(char *s, int *q, int *i, int **sum_q);

#endif