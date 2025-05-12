/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <gpolo@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:33:35 by gpolo             #+#    #+#             */
/*   Updated: 2025/04/10 12:12:39 by gpolo            ###   ########.fr       */
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
	if(!malloc_test((void*)e))
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

void	execute_command(char **cmd, t_env *env, char **envp)
{
	char	*str;
	char	**all_path;
	char	*path;

	str = find_path_index(env);
	all_path = ft_split(str, ':');
	if (cmd && cmd[0] && cmd [0][0] != '/')
	{
		path = find_path_access(all_path, cmd);
		if (!path)
		{
			free_args(all_path);
			free(str);
			printf("command not found\n");
			exit (127);
		}
	}
	else
		path = cmd[0];
	free_args(all_path);
	free(str);
//	bultings();
	execve(path, cmd, envp);
	printf("command not found\n");
	exit (127);
}
