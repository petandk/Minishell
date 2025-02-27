/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:15:13 by gpolo             #+#    #+#             */
/*   Updated: 2025/02/27 10:53:42 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_str(char *c, t_token *token, int i, int size_token)
{
	char	*str;

	if (!c || !token || i + 1 >= size_token || !token[i + 1].str)
		return (NULL);
	str = ft_strjoin(c, token[i + 1].str);
	if (!malloc_test((void *)str))
		exit (1);
	return (str);
}

void	in_out_file(char **file, char *str)
{
	char	*tmp;

	if (file && *file)
	{
		tmp = ft_strjoin(*file, str);
		if (!malloc_test((void *)tmp))
			exit(1);
		free (*file);
		*file = ft_strdup(tmp);
		if (!malloc_test((void *)file))
			exit(1);
		free (tmp);
	}
	else
	{
		*file = ft_strdup(str);
		if (!malloc_test((void *)*file))
			exit(1);
	}
}

void	init_comand(t_comand_data *comand, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		comand[i].in_file = NULL;
		comand[i].out_file = NULL;
		comand[i].comand = NULL;
		comand[i].quote = 0;
		i++;
	}
}

void	init_others(t_comand_data *comand, int j, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		comand[j].quote[i] = 0;
		comand[j].comand[i] = NULL;
		i++;
	}
	if (size > 0)
		comand[j].comand[size] = NULL;
}

int	count_comands(t_token *token, int size_token)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (i < size_token)
	{
		if (token[i].pipe)
			count++;
		i++;
	}
	return (count);
}
