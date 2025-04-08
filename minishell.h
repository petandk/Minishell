/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <gpolo@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:22:58 by gpolo             #+#    #+#             */
/*   Updated: 2025/04/08 12:24:44 by gpolo            ###   ########.fr       */
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

// COLORS //

# define C_START "\001"
# define C_END   "\002"

# define YELLOW  C_START "\033[33m" C_END
# define RED     C_START "\033[31m" C_END
# define GREY    C_START "\033[90m" C_END
# define RESET   C_START "\033[0m" C_END

// STRUCTS //

typedef struct s_token
{
	char	*str;
	int		greater_than;
	int		double_greater;
	int 	less_than;
	int		double_less;
	int		pipe;
	int		quote;
	int		quote_start;
	int 	quote_end;
}			t_token;

typedef struct s_token_data
{
	char	*str;
	char	c;
	int		i;
	int		j;
	int 	str_i;
	int 	in_quotes;
	int 	in_double_quotes;
	int		size_token;
	t_token	*token;
}			t_token_data;

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

typedef struct s_quotes
{
	int quote;
	int quote_start;
	int	quote_end;
}		t_quotes;

typedef struct s_comand_data
{
	char		**comand;
	char		**in_file;
	char		**out_file;
	t_quotes	*quote;
	int			in_count;
	int			out_count;
}				t_comand_data;

typedef struct s_quote
{
	int	in_single;
	int	in_double;
}			t_quote;

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

typedef struct	s_shell
{
	char	*prev_dir;
	t_env	*env;
}	t_shell;

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
void	ex_child(char *rl, char **envp);
int		find_path_index(char **envp);
char	*find_path_access(char **all_path, char **cmd);
void	execute_command(char **cmd, char **envp);

// token.c //

void    token(char *rl, char **envp);
int		execution(t_token *token, int size_token, char **envp);

//  token_utils.c //

int		ft_isspace(char c);
void	token_operator(t_token *token, char c, char next);
void	init_token(t_token *token, int size);
void	free_token(t_token **token, int size);
void	print_token_array(t_token *tokens, int size);
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

// count_tokens.c //

int		count_tokens(char *rl);

// token_split.c //

t_comand_data   *token_split(t_token *token, int size_token);

// prepare_to_execute.c //

int		prepare_to_execute(t_comand_data **comand, t_token *token, int size_token);

// the_files.c //

int	the_files(t_ind *ind, int size_token, t_token *token, t_comand_data **comand);

// execute_pipeline.c //

void	execute_pipeline(t_comand_data *commands, int cmd_count, char **envp);

// handle_redirections.c //

void	handle_redirections(char **in_file, char **out_file, int in_count, int out_count);

//handle_redirections_utils.c//

void    out_red(char *file);
void    append(char *file);
void    in_red(char *file);
void    here_doc(char *file);

// cd.c //

void	ft_cd(t_shell *shell, char *dest);

// echo.c //

void	ft_echo(char *msg, int is_n);

// pwd.c //

void	ft_pwd(void);

// export_utils.c //

t_env	*env_lstnew(char *name, char *val);
t_env	*env_lstlast(t_env	*env);
void	env_lstadd_back(t_env **env, t_env *newenv);
char	**	free_split(char **result, size_t i);
t_env	*create_env_list(char **envp);

// export.c //

void	swap_env_content(t_env *a, t_env *b);
void	sort_env_list(t_env	*envlist);
void	ft_show_env(t_env *envlist,int is_env);
void	ft_export(t_env *envlist, char *arg);
void	clear_env_list(t_env **envlist);

// utils.c //

int		malloc_test(void *str);

// pirnt_things.c //

void	print_token_array(t_token *tokens, int size);
void	print_args(char **args);
void	print_comands(t_comand_data *comand, int num_comands);

// env.c //

void	ft_env(t_env *envlist);

// split_first.c //

char	**split_first(char const *s, char c);

// unset.c //

int		ft_unset(t_env *envlist, char *name);

// exit.c //

void	ft_exit(t_shell **shell);

#endif		
