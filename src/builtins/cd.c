/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <rmanzana@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:49:34 by rmanzana          #+#    #+#             */
/*   Updated: 2025/05/29 18:45:53 by rmanzana         ###   ########.fr       */
/*   Updated: 2025/02/05 17:43:54 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*go_back(void)
{
	char	*current;
	char	*last_slash;

	current = getcwd(NULL, 0);
	if (current == NULL)
		return (NULL);
	if (ft_strncmp(current, "/", 2) == 0)
		return (current);
	last_slash = ft_strrchr(current, '/');
	if (last_slash)
	{
		*last_slash = '\0';
		if (*current == '\0')
		{
			free(current);
			return (ft_strdup("/"));
		}
	}
	return (current);
}

static char	*new_path(t_shell *shell, char *dest)
{
	char	*newpath;

	if ((!dest || ft_strncmp(dest, "", 1) == 0)
		|| (ft_strncmp(dest, "~", 1) == 0))
		newpath = go_home(shell);
	else if (ft_strncmp(dest, "..", 2) == 0)
		newpath = go_back();
	else if (ft_strncmp(dest, "-", 1) == 0)
	{
		if (!shell->prev_dir)
			return (ft_putendl_fd("cd: OLDPWD not set", 2), NULL);
		newpath = ft_strdup(shell->prev_dir);
		ft_putendl_fd(newpath, 1);
	}
	else
		newpath = ft_strdup(dest);
	return (newpath);
}

static int	update_pwd_env(t_env *env)
{
	char	*current;
	t_env	*current_node;

	current = getcwd(NULL, 0);
	if (!current)
		return (0);
	current_node = env;
	while (current_node && ft_strcmp(current_node->name, "PWD") != 0)
		current_node = current_node->next;
	if (current_node)
	{
		free(current_node->value);
		current_node->value = current;
	}
	else
	{
		free(current);
	}
	return (1);
}

static int	change_directory(t_shell *shell, char *dest,
		char *newpath, char *current)
{
	if (chdir(newpath) == -1)
	{
		shell->exit_status = 1;
		printerror("no_file", dest);
		free(newpath);
		free(current);
		free(dest);
		return (1);
	}
	free(shell->prev_dir);
	shell->prev_dir = current;
	update_oldpwd_env(shell, current);
	update_pwd_env(shell->env);
	free(newpath);
	free(dest);
	shell->exit_status = 0;
	return (0);
}

void	ft_cd(t_shell *shell, char *dest)
{
	char	*newpath;
	char	*current;

	current = getcwd(NULL, 0);
	if (!current)
	{
		shell->exit_status = 1;
		ft_putendl_fd("minishell: cd: getcwd error", 2);
		return ;
	}
	newpath = new_path(shell, dest);
	if (!newpath)
	{
		shell->exit_status = 1;
		free(current);
		return ;
	}
	change_directory(shell, dest, newpath, current);
}
