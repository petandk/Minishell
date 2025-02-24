/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:19:37 by gpolo             #+#    #+#             */
/*   Updated: 2025/02/19 14:12:58 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tn_splits(t_token *token, int size_token)
{
	int i ;
	int pipes;

	i = 0;
	pipes = 0;
	while (i < size_token)
	{
		if (token[i].pipe == 1)
			pipes++;
		if (token[i].pipe == 1 && i == (size_token - 1))
			return(-1);
		if (token[i].pipe == 1 && token[i + 1].pipe == 1)
			return(-1);
		i++;
	}
	return(pipes + 1);
}

t_comand_data	*token_split(t_token *token, int size_token)
{
	t_comand_data	*comand;
	int 			i ;
	int				j;
	int				nsplits;

	i = 0;
	j = 0;
	nsplits = tn_splits(token, size_token);
	if (nsplits == -1)
	{
		printf("Error: operadores de pipe incorrectos\n");
		return (NULL);
	}
	comand = malloc(nsplits * (sizeof(t_comand_data)));
	if	(!comand)
		return (NULL);
	while (i < size_token)
	{
		comand[j].
	}
	printf("number of operations --> %d\n",nsplits);
	return (comand);
}
