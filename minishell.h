/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <gpolo@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:22:58 by gpolo             #+#    #+#             */
/*   Updated: 2025/05/26 13:56:57 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES //

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <dirent.h>
# include <fcntl.h>
# include <termios.h>
# include <termcap.h>
# include <stddef.h>
# include <errno.h>

// COLORS //

# define C_START "\001"
# define C_END   "\002"

# define YELLOW  C_START "\033[33m" C_END
# define RED     C_START "\033[31m" C_END
# define GREY    C_START "\033[90m" C_END
# define RESET   C_START "\033[0m" C_END

// STRUCTS //

typedef struct s_quotes
{
	int quote;
	int quote_start;
	int	quote_end;
	int closed;	
}		t_quotes;

typedef struct s_token
{
	char		*str;
	int			greater_than;
	int			double_greater;
	int			less_than;
	int			double_less;
	int			pipe;
	t_quotes	quotes[16];
	int			quote_count;
}			t_token;

typedef struct s_token_data
{
	char	*str;
	char	c;
	int		i;
	int		j;
	int		str_i;
	int		size_token;
	t_token	*token;
}	t_token_data;

typedef struct s_ind
{
	int		i;
	int		j;
	int		k;
	int		size;
}			t_ind;

typedef struct s_quote_tracker
{
	int	open_pos;
	int	current_len;
	int	active;
}		t_quote_tracker;

typedef struct s_comand_data
{
	char		**comand;
	char		**in_file;
	char		**out_file;
	t_quotes	**quote;
	int			*quote_count;
	int			in_count;
	int			out_count;
}				t_comand_data;

typedef struct s_token_state
{
	int	in_single;
	int	in_double;
	int	in_token;
}	t_token_state;

typedef struct s_expan
{
	char	*new_str;
	int		i;
	int		j;
	int		start;
}			t_expan;

typedef struct s_fork_data
{
	int		i;
	int		pipefd[2];
	int		prev_fd;
	pid_t	pid;
}			t_fork_data;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	char	*prev_dir;
	t_env	*env;
	int		exit_status;
}	t_shell;

typedef struct s_heredoc
{
	char	*helper;
	char	*line;
	int		num_brackets;
}	t_heredoc;

typedef struct s_num_malloc
{
	int	*com;
	int	*in;
	int	*out;
}	t_num_malloc;

// reed_rl.c //

void	reed_rl(char *rl, char **envp);

// ex_child.c //

void	free_args(char **args);
char	*find_path_index(t_env *envp);
char	*find_path_access(char **all_path, char **cmd);
void	execute_command(char **cmd, t_shell *shell);

// token.c //

void	token(char *rl, t_shell *shell);

//	execution.c //

int		execution(t_token *token, int size_token, t_shell *shell);

//  token_utils.c //

int		ft_isspace(char c);
void	token_operator(t_token *token, char c, char next);
void	init_token(t_token *token, int size);
void	free_token(t_token **token, int size);
int		init_all(t_token_data *data, char *rl);

//  token_utils_2.c //

int		count_comands(t_token *token, int size_token);
void	init_others(t_comand_data *comand, int j, int size);
void	init_comand(t_comand_data *comand, int size);
void	in_out_file(char **file,char *str);
char	*init_str(char *c, t_token *token, int i, int size_token);

//  token_utils_3.c //

void	init_int_out(t_comand_data *comand, int size_in, int size_out);
int		check_in_out(int size_token, t_token *token);
void	in_out_size(t_comand_data *comand, t_ind ind, int size_token, t_token *token);
int		chek_token(t_token *token);
int		chek_double(char a, char b, int  *i);

//  token_utils_4.c //

void	free_t(char *str, t_token **token, int size);
void	init_quote_tracker(t_quote_tracker *qt);
void	quotes(t_token_data *data, t_quote_tracker *qt);
void	d_quotes(t_token_data *data, t_quote_tracker *qt);
int		finalize_token(t_token_data *data);

//  token_utils_5.c //

void	start_quote(t_token_data *data, t_quote_tracker *qt, t_token *curr_token);
void	end_quote(t_token_data *data, t_quote_tracker *qt, t_token *curr_token);
int		check_unclosed_quotes(t_token_data *data, int token_count);
char	*ft_strjoin_free(char *s1, char *s2);
int		is_in_single_quote(int i, t_quotes *quotes);
// count_tokens.c //

int		count_tokens(char *rl);

// token_split.c //

t_comand_data	*token_split(t_token *token, int size_token);

// prepare_to_execute.c //

int		prepare_to_execute(t_comand_data **comand, t_token *token, int size_token);

// the_files.c //

int	the_files(t_ind *ind, int size_token, t_token *token, t_comand_data **comand);

// execute_pipeline.c //

void	execute_pipeline(t_comand_data *commands, int cmd_count, t_shell *shell);

// handle_redirections.c //

void	handle_redirections(t_comand_data *cmd, t_shell *shell);

// handle_redirections_utils.c //

void    out_red(char *file);
void    append(char *file);
void    in_red(char *file);
void    here_doc(char **delimiters, int in_file, t_shell *shell, int expand);

// expancion_var.c //

void    expancion_var(t_comand_data *cmd, t_env *env);

// cd.c //

void	ft_cd(t_shell *shell, char *dest);

// cd_utils.c //

int	update_oldpwd_env(t_env *env, char *old_path);

// echo.c //

void	ft_echo(char **cmd);

// pwd.c //

void	ft_pwd(void);

// export_utils.c //

t_env	*env_lstnew(char *name, char *val);
t_env	*env_lstlast(t_env	*env);
void	env_lstadd_back(t_env **env, t_env *newenv);
char	**free_split(char **result, size_t i);
t_env	*create_env_list(char **envp);

// export_utils2.c //

t_env	*create_basic_env(void);
t_env	*find_env_var(t_env *envlist, char *name);
int		count_env_nodes(t_env *envlist);
void	clear_env_list(t_env **envlist);

// export.c //

void	swap_env_content(t_env *a, t_env *b);
void	sort_env_list(t_env	*envlist);
int		process_export(char *arg, char ***splitd, t_env *env_var, int is_env);
int		ft_export(t_env *envlist, char *arg);

// utils.c //

int		is_valid_name(char *name);
char	*ft_strstr(const char *haystack, const char *needle);
char	**list_to_matrix(t_env *env);
int		malloc_test(void *str);


// pirnt_things.c //

void	print_token_array(t_token *tokens, int size);
void	print_args(char **args);
void	print_comands(t_comand_data *comand, int num_comands);

// env.c //

t_env	*clone_env_list(t_env *envlist);
void	ft_show_env(t_env *envlist, int is_env);
void	ft_env(t_env *envlist, char **args);

// split_first.c //

void	*ft_free(char **strings, int count);
char	**split_first(char const *s, char c);

// unset.c //

int		ft_unset(t_env **envlist, char *name);

// exit.c //

void	ft_exit(t_shell **shell, int exit_code);

// heredoc.c //

t_list	*handle_heredoc(char *delimiter, t_shell **shell, int expand);
t_list	*ft_heredoc(char **input, int num_brackets, t_shell **shell, int expand);

// heredoc_utils.c //

char	*ft_replace(const char *str);
void	clean_heredoc(t_heredoc *vars);

// heredoc_utils2.c //

void	child_process_heredoc(t_shell **shell, char *delimiter, int pipe_fd, int expand);
int		process_line(char *line, char *delimiter, int pipe_fd);
void	sigint_handler(int sig);
int		ft_split_count(char **splited);
void	control_d_error(char *delimiter);

// heredoc_utils3.c //

char	*read_line_pipe(int fd);
t_list	*read_heredoc_pipe(int fd);

// heredoc_expansion.c //

char	*heredoc_expansion(char *str, t_shell **shell);

// builtins.c //

int		builtins(t_shell *shell, char **cmd);

#endif		
