/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_to_execute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:48:46 by gpolo             #+#    #+#             */
/*   Updated: 2025/02/27 16:34:11 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int inint_to_token(t_token *token, int size_token, t_comand_data **comand, t_ind *ind)
{
	int num_comands;

	ind->i = 0;
	ind->j = 0;
	num_comands = count_comands(token, size_token);
	*comand = malloc((num_comands) * sizeof(t_comand_data));
	if (!malloc_test((void *)*comand))
		exit(1);
	init_comand(*comand, num_comands);
	return(num_comands);
}

int pipe_size(int i, t_token *token, int size_token)
{
	int	size;
 
	size = 0;
	if (token[i].pipe)
			return (-1);
	while ((i + size) < size_token && !token[i + size].pipe)
	{
		if (!(token[i + size].str) && (token[i + size + 1].str))
			i += 2;
		else
			size++;
	}
	if ((size) == 0 && !token[size].str && (size + 1) >= size_token)
			return (-1);
	return (size);
}

void	strdup_comand(t_comand_data **comand, t_token *token, t_ind ind)
{
	int k;
	
	k = 0;
	while ((k < ind.size))
	{
		while (!(token[ind.i].str) && (token[ind.i + 1].str))
			ind.i += 2;	
		(*comand)[ind.j].comand[k] = ft_strdup(token[ind.i].str);
		if (token[ind.i].quote)
			(*comand)[ind.j].quote[k] = token[ind.i].quote;
		k++;
		ind.i++;
	}
}

void	the_comad(t_comand_data **comand, t_token *token, t_ind ind)
{
	(*comand)[ind.j].comand = (char **)malloc((ind.size + 1) * sizeof(char *));
	(*comand)[ind.j].quote = (int *)malloc((ind.size) * sizeof(int));
	if (!malloc_test((void *)(*comand)[ind.j].quote)
		|| !malloc_test((void *)(*comand)[ind.j].comand))
		exit(1);
	init_others(*comand, ind.j, ind.size);
	strdup_comand(comand, token, ind);
}

void	the_files(t_ind	*ind, int size_token, t_token *token, t_comand_data **comand)
{
	char *str;

	while (ind->i < size_token && !token[ind->i].pipe)
	{
		if (!token[ind->i].str)
		{
			if (ind->i + 1 < size_token && token[ind->i + 1].str)
			{
				if (token[ind->i].greater_than)
				{
					str = init_str(">", token, ind->i, size_token);
					in_out_file(&(*comand)[ind->j].out_file, str);
				}
				else if (token[ind->i].double_greater)
				{
					str=init_str("_", token, ind->i, size_token);
					in_out_file(&(*comand)[ind->j].out_file, str);
				}
				else if (token[ind->i].less_than)
				{
					str=init_str("<", token, ind->i, size_token);
					in_out_file(&(*comand)[ind->j].in_file, str);
				}
				else if (token[ind->i].double_less)
				{
					str=init_str("_", token, ind->i, size_token);
					in_out_file(&(*comand)[ind->j].in_file, str);
				}
				if (str)
					free (str);
			}
		}
		ind->i++;
	}
}
int prepare_to_execute(t_comand_data **comand, t_token *token, int size_token)
{
//	char	*str;
	int		num_comands;
	t_ind	ind;

	if (!token || size_token <= 0)
		return (-1);
	num_comands = inint_to_token(token, size_token, comand, &ind);
	while (ind.i < size_token)
	{
		ind.size = pipe_size(ind.i, token, size_token);
		if (!ind.size)
			return (-1);
		if (ind.size > 0)
			the_comad(comand, token, ind);
		the_files(&ind, size_token, token, comand);
		/*while (ind.i < size_token && !token[ind.i].pipe)
		{
			if (!token[ind.i].str)
			{
				if (ind.i + 1 < size_token && token[ind.i + 1].str)
				{
					if (token[ind.i].greater_than)
					{
						str = init_str(">", token, ind.i, size_token);
						in_out_file(&(*comand)[ind.j].out_file, str);
					}
					else if (token[ind.i].double_greater)
					{
						str=init_str(">>", token, ind.i, size_token);
						in_out_file(&(*comand)[ind.j].out_file, str);
					}
					else if (token[ind.i].less_than)
					{
						str=init_str("<", token, ind.i, size_token);
						in_out_file(&(*comand)[ind.j].in_file, str);
					}
					else if (token[ind.i].double_less)
					{
						str=init_str("<<", token, ind.i, size_token);
						in_out_file(&(*comand)[ind.j].in_file, str);
					}
					if (str)
						free (str);
				}
			}
			ind.i++;
		}*/
		if (ind.i < size_token && token[ind.i].pipe)
			ind.i++;
		ind.j++;
	}
	return (num_comands);
}
