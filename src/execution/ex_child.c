/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <gpolo@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:33:35 by gpolo             #+#    #+#             */
/*   Updated: 2025/05/31 13:21:46 by gpolo            ###   ########.fr       */
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
	t_env 	*path_env;

	path_env = find_env_var(envp, "PATH");
	if (!path_env || !path_env->value)
		return (NULL);
	e = ft_strdup(path_env->value);
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
	if (!str)
		return (NULL);
	all_path = ft_split(str, ':');
	if (cmd && cmd[0] && cmd [0][0] != '/' && cmd[0][0] != '.')
	{
		if (access(cmd[0], X_OK) == 0)
			return (cmd[0]);
		path = find_path_access(all_path, cmd);
		if (!path)
		{
			free_args(all_path);
			printf("%s: command not found\n", cmd[0]);
			free(str);
			return NULL;
		}
	}
	else
		path = cmd[0];
	free_args(all_path);
	free(str);
	return (path);
}

void	execute_command(char **cmd, t_shell *shell)
{
	char	*path;
	char	**new_env;

	new_env = list_to_matrix(shell->env);
	if (!new_env)
		exit(0);
	if (!cmd || !cmd[0])
		exit(0);
	path = get_command_path(shell, cmd);
	if (!path)
	{
		free_args(new_env);
//		printf("%s: No such file or directory\n", cmd[0]);
		return ;
	}
	execve(path, cmd, new_env);
	free_args(new_env);
	printf("%s: command not found\n", cmd[0]);
	return ;
}
