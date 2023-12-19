#ifndef MINISHELL_H
# define MINISHELL_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>
# include <libgen.h>
# include <errno.h>

# ifndef PIPE
#  define PIPE 124
# endif
# ifndef D
#  define D 34
# endif
# ifndef S
#  define S 39
# endif
# define SEP		1
# define COM		2
# define REDIR_OUT	3
# define REDIR_IN	4
# define HERE_DOC	5

//TODO: track if global right everywhere
extern int			g_minishell;

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
}					t_env;

typedef struct s_tokens
{
	char			*val;
	int				type;
	int				ind_command;
	int				ind_word;
	struct s_tokens	*next;
	struct s_tokens	*prev;
}		t_tokens;

typedef struct s_data
{
	char			*pwd;
	int				old_pwd;
	t_env			*env;
}					t_data;

typedef struct s_pipex
{
	pid_t			*pids;
	int				builtin;
	int				ac;
	int				paths_exist;
	int				redir_in;
	int				redir_out;
	int				rem_fd;
	int				pipes[2];
	int				here_doc;
	int				out;
	char			*here_doc_delim;
	char			*paths;
	char			*command;
	char			**args;
	char			**com_paths;
	char			**valid_env;
	t_tokens		*tokens;
	t_data			*data;
}					t_pipex;

/* shlvl.c */
int					ft_shlvl(t_env **env);
void				ft_export_shlvl(t_env **env, char *tok_val);

/* env.c */
int					ft_pwd_env_check(t_data *data, t_env **env, int add_env);
int					ft_store_env(t_data *data, char **env_orig);
int					ft_free_env(t_env *env, t_data *data);
int					ft_env_init(t_data *data, char **env);

/* error.c */
int					ft_error(char *val, char *error, int i);
void				ft_error_cd(char *str, int i);
int					ft_error_screen(char *str);
int					ft_export_error(t_tokens *toks, char *val, int ind);

/* builtin_utils.c */
t_tokens			*ft_too_many_args(t_tokens *toks, int i, int limit, char *com);
t_tokens			*ft_point_to_needed_tok(t_tokens *toks, int i, int next, int skip_char);
bool				ft_last_pipe(t_tokens *toks, int i);

/* builtin exit.c */
void				ft_exit_p(t_pipex *list, t_tokens *toks, int i);

/* builtin cd.c */
int					ft_cd(t_pipex *list, t_env *env, t_tokens *toks, int i);

/* builtin env.c */
int					ft_print_env_declare_x(t_env *env, int out);
int					ft_env(t_data *data, t_pipex *list, int i);

/* builtin echo.c */
int					ft_echo(t_pipex *list, t_tokens *toks, int i);

/* builtin pwd.c */
int					ft_pwd(t_pipex *list);

/* builtin export.c */
int					ft_export(t_pipex *list, t_tokens *toks, int i, t_env *env);
void				ft_repoint_env(t_env *tmp, t_env **new);
int					ft_add_to_env(t_env **env, char *val);

/* builtin unset.c */
void				ft_unset_p(t_pipex *list, t_tokens *toks, int i);
t_env				*ft_is_env(t_env *env, char *val, int i);

//free_more.c
void				ft_list_free(t_pipex *list);
char				*ft_free_new(char *new);
char				*ft_strjoin_char(char *str, char c);

// free.c
void				ft_list_loop_free(t_pipex *list, int i);
void				ft_free_av(char **av);
void				*save_free(void *s1, void *s2);
char				*ft_strjoin_free(char const *s1, char const *s2);
void				*ft_free_array(char **array);

//ft_command_split.c
char				**ft_command_split(char *s);
char				**ft_remove_quotes(char **av);

//ft_command_utils.c
int					ft_count_commands(char *s);
void				*ft_free_command(char **new);

// expander.c
char				*ft_expander(char *str, t_data *data);

/* init.c */
int					ft_init_list_loop(t_pipex *list, int i, int reidir_err);
int					init_pipex(t_pipex *list, t_data *data, t_tokens *toks);

// input_check.c
int					syntax_errors(char c);
int					check_input(char *s);

// input_utils.c
int					ft_strcmp(char *s1, char *s2);

/* exec.c */
int					ft_exec(t_data *data, t_tokens *toks);

/* exec_utils_more.c */
char				**ft_tok_to_args(t_tokens *toks, int i);
char				**ft_env_to_twod_arr(t_env *env_list);

/* exec_utils.c */
char				*ft_bcheck_paths(t_env *env);
void				ft_check_kid(int i, t_pipex *list);
char				*ft_gimme_com(t_tokens *toks, t_pipex *list, int i);
int					ft_right_out(t_pipex *list, int i);

/* redirects.c */
int					ft_redirects(int i, t_tokens **toks_orig, t_pipex *list);

/* tokenizing.c */
t_tokens			*ft_gimme_tokens(char **strs);
t_tokens			*ft_free_toks(t_tokens *toks);

/* builtins.c */
void				ft_builtins_p(t_pipex *list, int i, t_tokens *toks);
int					is_builtin(t_tokens *toks, int i);

/* main.c */
int					ft_find_tok(t_tokens *toks, int i);

// quote.c
int					is_quote(int c);
int					ft_is_space(char s);
int					check_open_quote(char *s);

// singal.c
void				get_sigint(int sig);
void				get_sigint_child(int sig);

// token.c
t_dlist				*ft_create_dlist(char *s, int quote);
void				ft_add_dlist_back(t_dlist **dl, char *str, int quote);
void				ft_token_loop(char *s, int *q, int *i, int **sum_q);

/* utils.c */
int					ft_find_index(char *s, char c);
int					ft_error_msg(char *msg, int msg_len);
int					ft_strlen_var(char *str);

#endif