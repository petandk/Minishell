/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:37:18 by gpolo             #+#    #+#             */
/*   Updated: 2025/02/23 15:35:37 by gpolo            ###   ########.fr       */
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

void	token_operator(t_token *token, char c, char next)
{
	token->str = NULL;
	if (c == '>' && next == '>')
		token->double_greater = 1;
	else if (c == '<' && next == '<')
		token->double_less = 1;
	else if (c == '>')
		token->greater_than = 1;
	else if (c == '<')
		token->less_than = 1;
	else if (c == '|')
		token->pipe = 1;
}

void	init_token(t_token *token, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		token[i].greater_than = 0;
		token[i].double_greater = 0;
		token[i].less_than = 0;
		token[i].double_less = 0;
		token[i].pipe = 0;
		token[i].quote = 0;
		i++;
	}
}

void	free_token(t_token **token, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free((*token)[i].str);
		i++;
	}
	free (*token);
}

int	init_all(t_token_data *data, char *rl)
{
	data->i = 0;
	data->j = 0;
	data->str_i = 0;
	data->in_quotes = 0;
	data->in_double_quotes = 0;
	data->size_token = count_tokens(rl);
	if (data->size_token == -1)
	{
		printf("Error: operadores de redirección incorrectos\n");
		return (0);
	}
	if (data->size_token == 0)
		return (0);
	data->str = malloc(ft_strlen(rl) * (sizeof(char)));
	data->token = malloc(data->size_token * (sizeof(t_token)));
	init_token(data->token , data->size_token);
	return (1);
}

void	print_token_array(t_token *tokens, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("Token %d:\n", i);
		printf("  str: %s\n", tokens[i].str);
		printf("  greater_than: %d\n", tokens[i].greater_than);
		printf("  double_greater: %d\n", tokens[i].double_greater);
		printf("  less_than: %d\n", tokens[i].less_than);
		printf("  double_less: %d\n", tokens[i].double_less);
		printf("  pipe: %d\n", tokens[i].pipe);
		printf("  quote: %d\n", tokens[i].quote);
		i++;
	}
}
