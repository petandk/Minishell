/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:32:15 by rmanzana          #+#    #+#             */
/*   Updated: 2025/05/31 13:22:50 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_name(char *name)
{
	int	i;

	if (!name || !name[0])
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_number(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	if (!*needle)
		return ((char *) haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (needle[j] && haystack[i + j] == needle[j])
			j++;
		if (!needle[j])
			return ((char *) &haystack[i]);
		i++;
	}
	return (NULL);
}

int	malloc_test(void *str)
{
	if (!str)
	{
		perror("Error in Malloc");
		return (0);
	}
	return (1);
}

char	**list_to_matrix(t_env *env)
{
	t_env	*current;
	char	**matrix;
	int		i;
	char	*joiner;

	current = env;
	i = 0;
	matrix = (char **)malloc(sizeof(char *) * (count_env_nodes(env) + 1));
	if (!matrix)
		return (NULL);
	while (current)
	{
		joiner = ft_strjoin(current->name, "=");
		if (!joiner)
			return (ft_free(matrix, i));
		matrix[i] = ft_strjoin(joiner, current->value);
		free(joiner);
		if (!matrix[i])
			return (ft_free(matrix, i));
		current = current->next;
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}
