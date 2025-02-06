/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <gpolo@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:22:58 by gpolo             #+#    #+#             */
/*   Updated: 2025/02/05 20:32:21 by rmanzana         ###   ########.fr       */
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

# define YELLOW	"\033[1;33m"
# define RED	"\033[1;31m"
# define GREY	"\033[0;90m"
# define RESET	"\033[0m"

// STRUCTS //

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

// reed_rl //

void	reed_rl(char *rl, char **envp);

// ex_child //

void	free_args(char **args);
void	ex_child(char *rl, char **envp);
int		find_path_index(char **envp);
char	*find_path_access(char **all_path, char **cmd);


// forks.c //

void	child(t_fork_data *fkd, int i, char **commands, char **envp);
void	father(t_fork_data *fkd, int i, char **commands);

// token.c //

void    token(char *rl);

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
t_env	*create_env_list(char **envp);

// export.c //
void	swap_env_content(t_env *a, t_env *b);
void	sort_env_list(t_env	*envlist);
void	ft_export(t_env *envlist);

#endif		
