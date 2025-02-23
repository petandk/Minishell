/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_to_execute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:48:46 by gpolo             #+#    #+#             */
/*   Updated: 2025/02/23 15:51:41 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *init_str(char *c, t_token *token, int i, int size_token)
{
	char	*str;
	
	if (!c || !token || i + 1 >= size_token || !token[i + 1].str)
		return (NULL);
	str=ft_strjoin(c, token[i + 1].str);
	if (!str)
	{
		perror("Error in ft_strjoin");
		exit (1);
	}
	return (str);
}

void	in_out_file(char **file,char *str)
{
	char	*tmp;

	if (file && *file)
	{
		tmp = ft_strjoin(*file, str);
		if (!tmp)
		{
			perror("Error in ft_strjoin"); // Corrección: Manejo de error
			exit(1);
		}
		free (*file);
		*file = ft_strdup(tmp);
		if (!*file)
		{
			perror("Error in ft_strdup"); // Corrección: Manejo de error
			exit(1);
		}
		free (tmp);
	}
	else
	{
		*file = ft_strdup(str);
		if (!*file)
		{
			perror("Error in ft_strdup"); // Corrección: Manejo de error
			exit(1);
		}
	}
}

void	init_comand(t_comand_data *comand, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		comand[i].in_file = NULL;
		comand[i].out_file = NULL;
		i++;
	}
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

void	init_others(t_comand_data *comand, int j, int size)
{
	int i;

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
int prepare_to_execute(t_comand_data **comand, t_token *token, int size_token)
{
	int		i;
	int		j;
	int		k;
	char	*str;
	int		num_comands;
	int		size;


	if (!token || size_token <= 0)
		return (-1);
	i = 0; 
	j = 0;
	num_comands = count_comands(token, size_token);
	printf("num comands = %d\n",num_comands);
	*comand = malloc((num_comands) * sizeof(t_comand_data));
	if (!*comand)
	{
		perror("Error allocating comand");
		exit(1);
	}
	init_comand(*comand, num_comands);
	while (i < size_token)
	{	
		if (!token[i].str && !token[i].pipe )
        {
            i++;
            continue;
        }
		size = 0;
		while ((i + size) < size_token && token[i + size].str && !token[i + size].pipe)
			size++;	
		if (size == 0 && token[i].pipe)
        {
            printf("Error: Pipe sin comando después.\n");
            return (-1);
        }
		if (size > 0)
		{
			(*comand)[j].comand = (char **)malloc((size + 1) * sizeof(char *));
			if (!(*comand)[j].comand)
			{
				perror("Error allocating comand array");
				exit(1);
			}
			(*comand)[j].quote = (int *)malloc((size) * sizeof(int));
			if (!(*comand)[j].quote)
			{
				perror("Error allocating quote array");
				exit(1);
			}
			init_others(*comand, j, size);
			k = 0;
			while ((k < size))
			{
				(*comand)[j].comand[k] = ft_strdup(token[i].str);
				if (token[i].quote)
					(*comand)[j].quote[k] = token[i].quote;
				k++;
				i++;
			}
		}
		while (i < size_token && !token[i].pipe)
		{
			if (!token[i].str)
			{
				if (i + 1 < size_token && token[i + 1].str)
				{
					if (token[i].greater_than)
					{
						str = init_str(">", token, i, size_token);
						in_out_file(&(*comand)[j].out_file, str);
					}
					else if (token[i].double_greater)
					{
						str=init_str(">>", token, i, size_token);
						in_out_file(&(*comand)[j].out_file, str);
					}
					else if (token[i].less_than)
					{
						str=init_str("<", token, i, size_token);
						in_out_file(&(*comand)[j].in_file, str);
					}
					else if (token[i].double_less)
					{
						str=init_str("<<", token, i, size_token);
						in_out_file(&(*comand)[j].in_file, str);
					}
					if (str)
						free (str);
				}
			}
			i++;
		}
		
		if (i < size_token && token[i].pipe)
			i++;
		j++;	
	}
	return (num_comands);
}
