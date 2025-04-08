/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:01:16 by gpolo             #+#    #+#             */
/*   Updated: 2025/04/08 11:51:54 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	init_string_array(char ***array, int size)
{
	int	i;

	if (!array || size <= 0)
		return ;
	*array = (char **)malloc(size * sizeof(char *));
	if (!*array)
		exit(1);
	i = 0;
	while (i < size)
	{
		(*array)[i] = NULL;
		i++;
	}
}

void	init_int_out(t_comand_data *comand, int size_in, int size_out)
{
	if (size_in > 0)
		init_string_array(&comand->in_file, size_in);
	if (size_out > 0)
		init_string_array(&comand->out_file, size_out);
}

void	in_out_size(t_comand_data *comand, t_ind ind,
			int size_token, t_token *token)
{
	comand->in_count = 0;
	comand->out_count = 0;
	while (ind.i < size_token && !token[ind.i].pipe)
	{
		if (!token[ind.i].str)
		{
			if (ind.i + 1 < size_token && token[ind.i + 1].str)
			{
				if (token[ind.i].greater_than || token[ind.i].double_greater)
					comand->out_count += 1;
				else if (token[ind.i].less_than || token[ind.i].double_less)
					comand->in_count += 1;
			}
		}
		ind.i++;
	}
}
