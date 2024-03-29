/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynguyen <ynguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:11:10 by vharkush          #+#    #+#             */
/*   Updated: 2024/01/30 20:17:04 by ynguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>
#include <libgen.h>
#include <errno.h>

#ifndef PIPE
#define PIPE 124
#endif
#ifndef D
#define D 34
#endif
#ifndef S
#define S 39
#endif
#define SEP 1
#define COM 2
#define REDIR_OUT 3
#define REDIR_IN 4
#define HERE_DOC 5
#define EMPTY_STR 6
#define FD_REDIR 7

extern volatile int		g_minishell;

typedef struct s_dlist
{
	char *str;
	int quote;
	struct s_dlist *prev;
	struct s_dlist *next;
} t_dlist;

typedef struct s_tlist
{
	char *comd;
	char **flargs;
	char *op;
	char **env;
	char **path;
	pid_t pid;
	char *doc;
	struct s_tlist *prev;
	struct s_tlist *next;
} t_tlist;

// Valeria'part
typedef struct s_env
{
	char *str;
	struct s_env *next;
} t_env;

typedef struct s_tokens
{
	char *val;
	int type;
	int ind_command;
	struct s_tokens *next;
	struct s_tokens *prev;
} t_tokens;

typedef struct s_data
{
	char			*pwd;
	int				old_pwd;
	int				expander_q;
	int				exit_code;
	t_env			*env;
}					t_data;

typedef struct s_pipex
{
	pid_t *pids;
	int builtin;
	int ac;
	int paths_exist;
	int redir_in;
	int redir_out;
	int fd_redir_out;
	int rem_fd;
	int pipes[2];
	int here_doc;
	int out;
	int n_flag_echo;
	int heredoc_c;
	int block_incr_redir;
	char *paths;
	char *command;
	char **args;
	char **com_paths;
	char **valid_env;
	t_tokens *tokens;
	t_data *data;
} t_pipex;

/* shlvl.c */
int ft_shlvl(t_env **env);
void ft_export_shlvl(t_env **env, char *tok_val);

/* env.c */
int ft_pwd_env_check(t_data *data, t_env **env, int add_env);
int ft_store_env(t_data *data, char **env_orig);
int ft_free_env(t_env *env, t_data *data);
int ft_env_init(t_data *data, char **env);

/* error.c */
int					ft_error(char *val, char *error, int i);
void				ft_error_cd(char *str, int i);
int					ft_error_screen(char *str);
int					ft_export_error(t_tokens *toks, char *val,
						int ind, t_pipex *list);
void				error_ms_out(char *delim, t_pipex *list, char *buf);

/* builtin_utils.c */
int					ft_end_space(t_tokens *toks, int i);
t_tokens			*ft_too_many_args(int i, int limit,
						char *com, t_pipex *list);
t_tokens			*ft_point_to_needed_tok(t_tokens *toks, int i, int next,
						int skip_char);
bool				ft_last_pipe(t_tokens *toks, int i);

/* builtin exit.c */
void ft_exit_p(t_pipex *list, t_tokens *toks, int i);

/* builtin cd.c */
int ft_cd(t_pipex *list, t_env *env, t_tokens *toks, int i);

/* builtin env.c */
int ft_print_env_declare_x(t_env *env, t_pipex *list);
int ft_env(t_data *data, t_pipex *list, int i);

/* builtin echo.c */
int ft_echo(t_pipex *list, t_tokens *toks, int i);

/* builtin echo_utils.c */
int ft_is_nflag_echo(t_tokens *toks);
int ft_n_flag_echo(int i, t_tokens **toks, t_pipex *list);

/* builtin pwd.c */
int ft_pwd(t_pipex *list);

/* builtin export_utils.c */
int					ft_check_export_err(int type, t_pipex *list);
int					ft_add_to_env(t_env **env, char *val);
void				ft_loop_export(t_pipex *list, t_tokens *toks,
						int i, int err);
int					ft_export(t_pipex *list, t_tokens *toks, int i, t_env *env);

/* builtin export.c */
int ft_check_before_equal(char *val);
void ft_repoint_env(t_env *tmp, t_env **new);
char *ft_cpyval(char *val, char *new);
int ft_check_after_equal(t_env *env, char *val);

/* builtin unset.c */
void ft_unset_p(t_pipex *list, t_tokens *toks, int i);
t_env *ft_is_env(t_env *env, char *val, int i);

// free_more.c
void ft_list_free(t_pipex *list);
char *ft_free_new(char *new);
char *ft_strjoin_char(char *str, char c);
t_tokens *ft_free_toks(t_tokens *toks);

// free.c
void ft_list_loop_free(t_pipex *list, int i, int pipe_err);
void ft_free_av(char **av);
void *save_free(void *s1, void *s2);
char *ft_strjoin_free(char const *s1, char const *s2);
void *ft_free_array(char **array);

/* command_checks.c */
char *ft_gimme_com(t_tokens *toks, t_pipex *list, int i);
char **ft_tok_to_args(t_tokens *toks, int i, int y);
bool ft_command_check(t_pipex *list, t_tokens *toks, int i);

// ft_command_split.c
char **ft_command_split(char *s);
char **ft_remove_quotes(char **av);

// ft_command_utils.c
int ft_count_commands(char *s);
void *ft_free_command(char **new);

// ft_expander_utils.c
int ft_word_count(char *str);
void find_dquote(char *str, char *tmp1, int *i, int *y);
char *ft_add_quotes(char *str, int i, int y);
char *ft_get_var(char *str, t_data *data);
char *ft_name_var(char *s);

// ft_expander.c
char *ft_expander(char *str, t_data *data);

//heredoc_utils.c
int					ft_is_heredoc(char *new);
t_tokens			*ft_syntax_err_redir(t_tokens *toks, int i, t_pipex *list);
char				*ft_expand_heredoc(char *buf, int buf_len, t_data *data);

/* init.c */
int ft_init_list_loop(t_pipex *list, int i, int reidir_err);
int init_malloc_pipex(t_pipex *list, t_data *data,
					  t_tokens *toks);

// input_check.c
int					syntax_errors(char c, t_data *data);
int					check_open_quote(char *s, t_data *data);
int					check_input(char *s, t_data *data);

// wait_n_cmp.c
char				*ft_bcheck_paths(t_env *env);
void				ft_wait_for_my_babies(t_pipex *list, int status);
int					ft_strcmp(char *s1, char *s2);
void				ft_change_ac_on_err(t_tokens *iter, int i);

/* exec.c */
int ft_exec(t_data *data, t_tokens *toks);
void free_loop_children(t_pipex *list, int *i);

/* exec_utils.c */
void ft_check_kid(int i, t_pipex *list);
int ft_right_out(t_pipex *list, int i);
char **ft_env_to_twod_arr(t_env *env_list);

/* redirects_utils.c */
int ft_is_echo_last(t_tokens *toks, int i);
void ft_change_args(t_tokens **toks);
void ft_del_com(t_pipex **list, t_tokens **tokens,
				int i, int completely);
int ft_redirout_no_com(t_tokens *toks, int i,
					   t_pipex *list, int err);

/* redirects.c */
int ft_redirects(int i, t_tokens *toks, t_pipex *list);

/* redir_heredoc.c */
char *ft_change_buf(char *env_var, char **buf, int i);
int ft_heredoc_set(t_tokens **toks, t_pipex *list,
				   int i, int err);
int ft_heredoc_exec(char *delim, t_pipex *list);

// tokenizing_utils.c
char *ft_tok_val(char *str, int *y, int echo, int redir);
char *ft_val_is_not_a_word(char *str, int *y);
int ft_tok_type(char *value, int redir);
bool ft_type_redir(char *str, char c, int redir);

/* tokenizing.c */
int ft_quotecho_condition(char **val, int y, char *str, int *i);
t_tokens *ft_gimme_tokens(char **strs);

/* builtins.c */
void				ft_builtins_p(t_pipex *list, int i, t_tokens *toks);
int					is_builtin(t_tokens *toks, int i);
bool				ft_builtin_check(char *command, int com_len,
						char *to_compare, int to_comp_len);
void				ft_free_exit_builtin(t_pipex *list, int i);

/* main.c */
int ft_find_tok(t_tokens *toks, int i);

// quote.c
int is_quote(int c);
int is_open_quote(int c);
int ft_is_space(char s);
int ft_quote_condition(char **val, int y, char *str, int *i);
char *ft_get_var_no_quote(char *buf, t_data *data, int ind);

// singal.c
void				sig_handel(int sig, t_data *data);
void				get_sig_child(int sig);
void				get_sig_parent(int sig);
void				get_sig_heredoc(int sig);
void				allocate_sig(t_pipex **list, int *i);

// token.c
t_dlist *ft_create_dlist(char *s, int quote);
void ft_add_dlist_back(t_dlist **dl, char *str, int quote);
t_tokens *ft_open_file(t_tokens *toks, t_pipex *list,
					   int i, int out);
int ft_quotecho_condition(char **val, int y, char *str,
						  int *i);

/* utils.c */
int ft_find_index(char *s, char c);
int ft_error_msg(char *msg, int msg_len);
int ft_strlen_var(char *str);
int after_dollar(char next);
void ft_assign_prev_cur_tok(t_tokens **toks);

#endif