/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <gpolo@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:33:35 by gpolo             #+#    #+#             */
/*   Updated: 2025/04/01 17:43:09 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

int	find_path_index(char **envp)
{
	int		i;
	char	*str;
	int		j;

	i = 0;
	str = "PATH=";
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] == str[j] && str[j] != '\0')
			j++;
		if (str[j] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

char	*find_path_access(char **all_path, char **cmd)
{
	int		i;
	char	*n_cmd;
	char	*path;

	n_cmd = ft_strjoin("/", cmd[0]);
	if (!n_cmd)
		return (NULL);
	i = 0;
	while (all_path[i])
	{
		path = ft_strjoin(all_path[i++], n_cmd);
		if (!path)
		{
			free (n_cmd);
			return (NULL);
		}
		if (access(path, X_OK) == 0)
			break ;
		free (path);
	}
	free (n_cmd);
	if (all_path[i] == NULL)
		return (NULL);
	return (path);
}

void	execute_command(char **cmd, char **envp)
{
	int		i;
	char	**all_path;
	char	*path;

	i = find_path_index(envp);
	all_path = ft_split(envp[i] + 5, ':');
	if (cmd && cmd[0] && cmd [0][0] != '/')
	{
		path = find_path_access(all_path, cmd);
		if (!path)
		{
			free_args(all_path);
			printf("command not found\n");
			exit (127);
		}
	}
	else
		path = cmd[0];
	free_args(all_path);
	execve(path, cmd, envp);
	printf("command not found\n");
	exit (127);
}

void	ex_child(char *rl, char **envp)
{
	char	**cmd1;

	cmd1 = ft_split(rl, ' ');
	if (!cmd1)
		exit (1);
	execute_command(cmd1, envp);
	exit (1);
}
