/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:00:10 by gpolo             #+#    #+#             */
/*   Updated: 2025/05/12 11:55:02 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_quote(t_token_data *data, t_quote_tracker *qt,
			t_token *curr_token)
{
	int	idx;

	idx = curr_token->quote_count;
	curr_token->quotes[idx].quote_start = data->str_i;
	curr_token->quotes[idx].quote_end = -1;
	curr_token->quotes[idx].closed = 0;
	if (data->c == '\'')
	{
		curr_token->quotes[idx].quote = 1;
		qt->active = 1;
	}
	else
	{
		curr_token->quotes[idx].quote = 2;
		qt->active = 2;
	}
	curr_token->quote_count++;
	qt->open_pos = data->str_i;
}

void	end_quote(t_token_data *data, t_quote_tracker *qt, t_token *curr_token)
{
	int	idx;

	idx = curr_token->quote_count - 1;
	curr_token->quotes[idx].quote_end = data->str_i - 1;
	curr_token->quotes[idx].closed = 1;
	qt->active = 0;
}

int	check_unclosed_quotes(t_token_data *data, int token_count)
{
	int		tok_i;
	int		q_i;
	t_token	*curr_token;

	tok_i = 0;
	while (tok_i < token_count)
	{
		curr_token = &data->token[tok_i];
		q_i = 0;
		while (q_i < curr_token->quote_count)
		{
			if (!curr_token->quotes[q_i].closed)
			{
				printf("NO CLOSED PIPIES\n");
				return (1);
			}
			q_i++;
		}
		tok_i++;
	}
	return (0);
}
