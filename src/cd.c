/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <rmanzana@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:49:34 by rmanzana          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/05 15:10:31 by gpolo            ###   ########.fr       */
=======
/*   Updated: 2025/02/05 17:43:54 by rmanzana         ###   ########.fr       */
>>>>>>> development
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
<<<<<<< HEAD
/*
static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	while ((s1[index] || s2[index]) && index < n)
	{
		if ((unsigned char)s1[index] != (unsigned char)s2[index])
			return ((unsigned char)s1[index] - (unsigned char)s2[index]);
		index++;
	}
	return (0);
}

static char	*ft_strrchr(const char *s, int c)
{
	int	index;

	index = 0;
	while (s[index])
		index++;
	while (index > 0)
	{
		if (s[index] == (unsigned char)c)
			return ((char *)s + index);
		index--;
	}
	if (s[index] == (unsigned char)c)
		return ((char *)s + index);
	return (NULL);
}
*/
char	*go_home(void)
=======

static char	*go_home(void)
>>>>>>> development
{
	char	*home;

	home = getenv("HOME");
	if (home == NULL)
		return (perror("getenv home error"), NULL);
	return (home);
}

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
		*last_slash = '\0';
	return (current);
}

void	ft_cd(t_shell *shell, char *dest)
{
	char	*newpath;
	char	*current;
	int		ret;

	current = getcwd(NULL, 0);
	if ((ft_strncmp(dest, "", 1) == 0) || (ft_strncmp(dest, "~", 1) == 0))
		newpath = go_home();
	else if (ft_strncmp(dest, "..", 2) == 0)
		newpath = go_back();
	else if (ft_strncmp(dest, "-", 1) == 0)
		newpath = shell->prev_dir;
	else
		newpath = dest;
	if (!newpath)
		exit(1);
	ret = chdir(newpath);
	if (ret == -1)
	{
		perror("cd error");
		if (ft_strncmp(dest, "..", 2) == 0)
			free(newpath);
		exit(1);
	}
	free(shell->prev_dir);
	shell->prev_dir = current;
	if (ft_strncmp(dest, "..", 2) == 0)
		free(newpath);
}
/*
int	main(int argc, char *argv[])
{
	char	*oldpath;
	char	*newpath;
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	oldpath = getcwd(NULL, 0);
	shell->prev_dir = ft_strdup(oldpath);
	printf("Old path: %s\n", oldpath);
	if (argc < 2)
		ft_cd(shell, "");
	else
		ft_cd(shell, argv[1]);
	newpath = getcwd(NULL, 0);
	printf("New path: %s\n", newpath);
	free(shell->prev_dir);
	free(shell);
	free(oldpath);
	free(newpath);
	return (0);
<<<<<<< HEAD
}*/
=======
}
*/
>>>>>>> development
