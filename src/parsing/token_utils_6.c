/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:01:55 by gpolo             #+#    #+#             */
/*   Updated: 2025/06/09 10:51:10 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_quotes(char *str, int i, int q, int in_quote)
{
	while (str[i])
	{
		if ((str[i] == '\'') || (str[i] == '"'))
		{
			if (!in_quote)
			{
				in_quote = str[i];
				q++;
			}
			else if (in_quote == str[i])
			{
				in_quote = 0;
				q++;
			}
		}
		i++;
	}
	if ((q % 2) > 0)
		return (q / 2 + 1);
	return (q / 2);
}

void	copy_quotes(t_quotes *dst, t_quotes *src, int count)
{
	int	q;

	q = 0;
	while (q < count)
	{
		dst[q].quote = src[q].quote;
		dst[q].quote_start = src[q].quote_start;
		dst[q].quote_end = src[q].quote_end;
		q++;
	}
	dst[q].quote = 0;
	dst[q].quote_start = -1;
	dst[q].quote_end = -1;
}

void	alloc_and_copy1(t_comand_data *cmd, t_token *token, t_ind *ind, int k)
{
	int	count;

	count = token[ind->i].quote_count;
	cmd->quote[k] = malloc(sizeof(t_quotes) * (count + 1));
	if (!malloc_test(cmd->quote[k]))
		exit(1);
	cmd->comand[k] = ft_strdup(token[ind->i].str);
	cmd->quote_count[k] = count;
	copy_quotes(cmd->quote[k], token[ind->i].quotes, count);
}

int	chek_double(char a, char b, int *i)
{
	if (a == b)
	{
		*i += 2;
		return (1);
	}
	return (0);
}

int	check_in_out(int size_token, t_token *token)
{
	int	i;

	i = 0;
	while (i < size_token)
	{
		if (!token[i].str && i == (size_token - 1))
			return (0);
		else if ((!token[i].str && !token[i].pipe) && ((!token[i + 1].str)
				|| (token[i + 1].pipe)))
			return (0);
		i++;
	}
	return (1);
}
