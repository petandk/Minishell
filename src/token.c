/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <gpolo@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:18:35 by gpolo             #+#    #+#             */
/*   Updated: 2025/02/06 15:49:49 by gpolo            ###   ########.fr       */
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

int	count_tokens(char *rl)
{
	int i;
	int in_quotes;
	int in_double_quotes;
	int tokens;

	i = 0;
	in_quotes = 0;
	in_double_quotes = 0;
	tokens = 0;
	while (rl[i])
	{
		if (rl[i] == '\'' && !in_double_quotes)
		{
			in_quotes = !in_quotes;
			i++;
			continue;
		}
		else if (rl[i] == '"' && !in_quotes)
		{
			in_double_quotes = !in_double_quotes;
			i++;
			continue;
		}
		if (!in_quotes && !in_double_quotes)
		{
			if (ft_isspace(rl[i]) || ft_strchr("<>|", rl[i]))
			{
				if (i > 0 && !ft_isspace(rl[i - 1]) && !ft_strchr("<>|", rl[i - 1]))
					tokens++;
				if (ft_strchr("<>|", rl[i]))
					tokens++;
			}
		}
		i++;
	}
	if (i > 0 && !ft_isspace(rl[i - 1]) && !ft_strchr("<>|", rl[i - 1]))
		tokens++;
	return (tokens);
}

void	token_operator(t_token *token, char c)
{
	token->str = NULL;
//	printf(">> %c <<", c);
	if (c == '>')
		token->greater_than = 1;
	if (c == '<')
		token->less_than = 1;
	if (c == '|')
		token->pipe = 1;
}

void	init_token(t_token *token, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		token[i].greater_than = 0;
		token[i].less_than = 0;
		token[i].pipe = 0;
		i++;
	}
}

void	print_token_array(t_token *tokens, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		printf("Token %d:\n", i);
		printf("  str: %s\n", tokens[i].str);
		printf("  greater_than: %d\n", tokens[i].greater_than);
		printf("  less_than: %d\n", tokens[i].less_than);
		printf("  pipe: %d\n", tokens[i].pipe);
		i++;
	}
}

void	token(char *rl)
{
	char	*str;
	char	c;
	int		i;
	int		j;
	int 	str_i;
	int 	in_quotes;
	int 	in_double_quotes;
	int		size_token;
	t_token	*token;

	i = 0;
	j = 0;
	str_i = 0;
	in_quotes = 0;
	in_double_quotes = 0;
	size_token = count_tokens(rl);
	str = malloc(ft_strlen(rl) * (sizeof(char)));
	token = malloc(size_token * (sizeof(t_token)));
	init_token(token , size_token);
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
				if (str_i > 0)
				{
					str[str_i] = '\0';
					token[j++].str = ft_strdup(str);
					printf("Token: %s\n", str);
					str_i = 0;
				}
				i++;
				continue;
			}
			if (ft_strchr("<>|", c))
			{
				if (str_i > 0)
				{
					str[str_i] = '\0';
					token[j++].str = ft_strdup(str);
					printf("Token: %s\n", str);
					str_i = 0;
				}
				token_operator(&token[j++] , c);
				printf("operator: %c\n", c);
				i++;
				continue;
			}
			str[str_i++] = c;
		}
		else 
			str[str_i++] = c;
		i++;
	}
	if (str_i > 0)
	{
		str[str_i] = '\0';
		token[j++].str = ft_strdup(str);
		printf("Token: %s\n", str);
	}
	print_token_array(token, size_token);
}
