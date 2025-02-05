/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <gpolo@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:22:58 by gpolo             #+#    #+#             */
/*   Updated: 2025/02/05 15:38:00 by gpolo            ###   ########.fr       */
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

// COLORS //

# define C_START "\001"
# define C_END   "\002"

# define YELLOW  C_START "\033[33m" C_END
# define RED     C_START "\033[31m" C_END
# define GREY    C_START "\033[90m" C_END
# define RESET   C_START "\033[0m" C_END

// STRUCTS //

typedef struct s_fork_data
{
	int		i;
	int		pipefd[2];
	int		prev_fd;
	pid_t	pid;
}			t_fork_data;

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

#endif
