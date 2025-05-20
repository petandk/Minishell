/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <gpolo@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:33:35 by gpolo             #+#    #+#             */
/*   Updated: 2025/05/20 11:41:42 by gpolo            ###   ########.fr       */
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

char	*find_path_index(t_env *envp)
{
	char	*e;

	e = ft_strdup(find_env_var(envp, "PATH")->value);
	if (!malloc_test((void *)e))
		return (NULL);
	return (e);
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

static char	*get_command_path(t_shell *shell, char **cmd)
{
	char	*str;
	char	**all_path;
	char	*path;

	str = find_path_index(shell->env);
	all_path = ft_split(str, ':');
	if (cmd && cmd[0] && cmd [0][0] != '/')
	{
		path = find_path_access(all_path, cmd);
		if (!path)
		{
			free_args(all_path);
			printf("%s: command not found\n", cmd[0]);
			free(str);
			exit (127);
		}
	}
	else
		path = cmd[0];
	free_args(all_path);
	free(str);
	return (path);
}

void	execute_command(char **cmd, t_shell *shell, char **envp)
{
	char	*path;

	if (!cmd || !cmd[0])
		exit(0);
	if (ft_strcmp(cmd[0], "exit") == 0 || ft_strcmp(cmd[0], "cd") == 0)
		exit(0);
	path = get_command_path(shell, cmd);
	if (builtins(shell, cmd))
	{
		if (path != cmd[0])
			free(path);
		exit(0);
	}
	else
	{
		execve(path, cmd, envp);
		printf("%s: command not found\n", cmd[0]);
		exit (127);
	}
}
