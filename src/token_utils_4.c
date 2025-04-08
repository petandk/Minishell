/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:58:18 by gpolo             #+#    #+#             */
/*   Updated: 2025/04/08 12:39:51 by gpolo            ###   ########.fr       */
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
	if (qt->active == 1)
	{
		data->token[data->j].quote = 1;
		data->token[data->j].quote_start = qt->open_pos;
		data->token[data->j].quote_end = qt->current_len;
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
	if (qt->active == 2)
	{
		data->token[data->j].quote = 2;
		data->token[data->j].quote_start = qt->open_pos;
		data->token[data->j].quote_end = qt->current_len;
		init_quote_tracker(qt);
	}
	else
	{
		qt->active = 2;
		qt->open_pos = data->str_i;
	}
	data->i++;
}
