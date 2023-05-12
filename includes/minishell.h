/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:02:21 by ymehlil           #+#    #+#             */
/*   Updated: 2023/04/30 20:42:06 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../ft_printf/ft_printf.h"
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern int			g_exit_status;

typedef enum type
{
	NONE,
	ARG,
	FILE_IN,
	HERE_DOC,
	FILE_OUT,
	FILE_OUT_SUR,
	OPEN_FILE,
	LIMITOR,
	EXIT_FILE,
	EXIT_FILE_RET,
	QUOTE
}					t_type;

typedef struct token
{
	char			*word;
	enum type		type;
	struct token	*next;
}					t_token;

typedef struct s_fds
{
	int				fd;
	struct s_fds	*next;
}					t_fds;

typedef struct cmd_line
{
	char			*cmd;
	struct token	**token;
	char			**args;
	struct cmd_line	**first;
	struct cmd_line	*next;
}					t_cmds;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

int					main(int ac, char **av, char **env);
t_fds				**get_fds(void);
int					ft_tokenise(t_cmds **cmd_line);
void				ft_lstadd_back_token(t_token **lst, t_token *new);
int					ft_add_fd(int fd);
char				**ft_dark_split(char *str, char sep, int d, int s);
char				**ft_dark_split_token(char *str);

t_token				**ft_create_token(char *str);
t_token				*ft_lstnew_token(char *word);
t_token				*ft_lstlast_token(t_token *lst);
int					ft_expend_words(t_token **token);

t_cmds				*ft_create_cmd_line(char *str);
t_cmds				**ft_parse_line(char *str);

char				**ft_dark_split_token(char *str);
int					ft_check_dir(char *str);

int					ft_create_args(t_cmds *cmd);

int					ft_cd(char **args, t_env **env);
void				ft_echo(char **args);
void				ft_env(char **av);
void				ft_pwd(char **args);

int					nb_words(char *str);
char				*ft_expend(char *str, enum type type, int i, int j);
int					nb_str(char *str);
char				*ft_quote_value(char *str);
int					ft_check_quote_value(char *str);
t_env				*ft_init_env(char **env);
int					check_args(char **av);
int					ft_darkisalnum(char c);
int					ft_get_value(char **str, char *tmp);
char				*ft_expend_d(char *str, int i, int j);
char				*ft_join_parts(char **tab, int len_tab);
char				*ft_create_part(char *str, int end);
void				ft_add_back_env(char *str, t_env **env_list);
t_env				*ft_check_name(char *name, t_env *env_list);

void				ft_free_cmdslst(t_cmds **cmds);
void				ft_free_tab(char **tab, int nb);
int					ft_export(char **av, t_env **env_list, int i);
void				ft_unset(char **args, t_env **env_list);
void				ft_free_env(t_env **env);
t_env				**get_adress(void);
t_env				*ft_get_env(char *name);
int					ft_exit(char **av, t_cmds **cmds);
int					ft_is_int(char *str);
char				*white_get_env(char *name);
int					ft_set_redir(t_token *token, int saved_stdin,
						int saved_stdout);
int					ft_execution(t_cmds **cmds);
char				**env_to_str(t_env *env_list);
int					ft_single_exec(t_cmds *cmd, t_cmds **cmds);
int					ft_here_doc(t_token *token, int saved_stdin,
						int saved_stdout, char *str);
void				ft_signal(int sig);
int					update_quotes(char *str, int i, int *d, int *s);
int					ft_redir(t_token **token, int saved_stdin,
						int saved_stdout);
char				*ft_get_path(char **path, char *cmd);
int					ft_is_builtin(char *cmd_name);
int					ft_execve_b(char **args, t_cmds **cmds);
int					ft_execve_s(char **args, t_cmds **cmds, int *tmp,
						int *svd_standart);
void				setup_pipes(int *fd_in, int *fd, t_cmds *cur);
void				cleanup_pipes(int *fd_in, int *fd);
int					ft_darkisalnum(char c);
int					ft_check_dollars(char *str);
char				*ft_quote_value(char *str);
char				*ft_join_parts(char **tab, int len_tab);
int					ft_create_str(char *str, char **part);
int					find_stop_index(char *str, int i);
int					get_env_list_length(t_env *env_list);
char				**allocate_env_str_array(int len);
void				set_next_type(t_token *current);
void				set_token_type(t_token *current);
int					ft_set_type(t_token **token);
void				ft_print_exit_free_all(t_cmds **cmds);
void				ft_signal_hd(int sig);
int					len_cmd(t_cmds **cmds);
void				get_cmd_code(pid_t pid);
char				*clean_up_lim(char *str, int i, int j);
int					execute_command(t_cmds *cur, int *fd_in, int *svd_standart,
						pid_t *child_pid);
int					ft_trigger(char **args, t_cmds **cmds, char **tmp);
char				**ft_parse_env(int i, int j);
int					is_here_doc(t_cmds *cmds);
int					find_stop_index_hd(char *str);
int					nb_str_hd(char *str);
int					ft_get_value_hd(char **str);
t_env				*ft_add_env(char *line);
char				*dark_strtrim(const char *s1, const char *set);
void				ft_signal_cat(int sig);
void				ft_print_export(char **av);
int					len_cmd(t_cmds **cmds);
int					is_directory(const char *path);
int					handle_errno_and_exit(void);

#endif
