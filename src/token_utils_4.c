/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:58:18 by gpolo             #+#    #+#             */
/*   Updated: 2025/05/20 12:34:46 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_t(char *str, t_token **token, int size)
{
	free(str);
	free_token(token, size);
}

void	init_quote_tracker(t_quote_tracker *qt)
{
	qt->open_pos = -1;
	qt->current_len = 0;
	qt->active = 0;
}

void	quotes(t_token_data *data, t_quote_tracker *qt)
{
	t_token	*curr_token;
	int		idx;

	curr_token = &data->token[data->j];
	if (qt->active == 1)
	{
		idx = curr_token->quote_count;
		if (idx < 16)
		{
			curr_token->quotes[idx].quote = 1;
			curr_token->quotes[idx].quote_start = qt->open_pos;
			curr_token->quotes[idx].quote_end = data->str_i - 1;
			curr_token->quote_count++;
		}
		init_quote_tracker(qt);
	}
	else
	{
		qt->active = 1;
		qt->open_pos = data->str_i;
	}
	data->i++;
}

void	d_quotes(t_token_data *data, t_quote_tracker *qt)
{
	t_token	*curr_token;
	int		idx;

	curr_token = &data->token[data->j];
	if (qt->active == 2)
	{
		idx = curr_token->quote_count;
		if (idx < 16)
		{
			curr_token->quotes[idx].quote = 2;
			curr_token->quotes[idx].quote_start = qt->open_pos;
			curr_token->quotes[idx].quote_end = data->str_i - 1;
			curr_token->quote_count++;
		}
		init_quote_tracker(qt);
	}
	else
	{
		qt->active = 2;
		qt->open_pos = data->str_i;
	}
	data->i++;
}

int	finalize_token(t_token_data *data)
{
	int	i;

	if (data->str_i > 0)
	{
		data->str[data->str_i] = '\0';
		data->token[data->j].str = ft_strdup(data->str);
		data->j++;
	}
	i = check_unclosed_quotes(data, data->j);
	return (i);
}
