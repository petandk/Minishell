/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <gpolo@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:18:35 by gpolo             #+#    #+#             */
/*   Updated: 2025/02/05 15:28:21 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if ((c == 32) || ((c >= 9) && (c <= 13)))
		return (1);
	else
		return (0);
}

void	token(char *rl)
{
	char	token[1024];
	char	c;
	int		i;
	int 	token_i;
	int 	in_quotes;
	int 	in_double_quotes;

	i = 0;
	token_i = 0;
	in_quotes = 0;
	in_double_quotes = 0;
	while (rl[i])
	{
		c = rl[i];
		if (c == '\'' && !in_double_quotes)
		{
			in_quotes = !in_quotes;
			i++;
			continue;
		}
		else if (c == '\"' && !in_quotes)
		{
			in_double_quotes = !in_double_quotes;
			i++;
			continue;
		}
		if (!in_quotes && !in_double_quotes)
		{
			if(ft_isspace(c))
			{
				if (token_i > 0)
				{
					token[token_i] = '\0';
					printf("Token: %s\n", token);
					token_i = 0;
				}
				i++;
				continue;
			}
			if (ft_strchr("<>|", c))
			{
				if (token_i > 0)
				{
					token[token_i] = '\0';
					printf("Token: %s\n", token);
					token_i = 0;
				}
				printf("operator: %c\n", c);
				i++;
				continue;
			}
			token[token_i++] = c;
		}
		else 
			token[token_i++] = c;
		i++;
	}
	if (token_i > 0)
	{
		token[token_i] = '\0';
		printf("Token: %s\n", token);
	}
}
