/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <gpolo@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:18:35 by gpolo             #+#    #+#             */
/*   Updated: 2025/04/08 12:40:16 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_quotes(t_token_data *data, t_quote_tracker *qt, char next)
{
	if (data->c == '\'' && qt->active != 2)
	{
		if (data->c == next)
		{
			data->i += 2;
			return (1);
		}
		quotes(data, qt);
		return (1);
	}
	else if (data->c == '\"' && qt->active != 1)
	{
		if (data->c == next)
		{
			data->i += 2;
			return (1);
		}
		d_quotes(data, qt);
		return (1);
	}
	return (0);
}

static void	operator(t_token_data *data, char *rl)
{
	if (data->str_i > 0)
	{
		data->str[data->str_i] = '\0';
		data->token[data->j++].str = ft_strdup(data->str);
		data->str_i = 0;
	}
	if ((data->c == '>' && rl[data->i + 1] == '>')
		|| (data->c == '<' && rl[data->i + 1] == '<'))
	{
		token_operator(&data->token[data->j++], data->c, rl[data->i + 1]);
		data->i++;
	}
	else
		token_operator(&data->token[data->j++], data->c, '\0');
}

static int	process_outside_quotes(t_token_data *data, char *rl)
{
	if (ft_isspace(data->c))
	{
		if (data->str_i > 0)
		{
			data->str[data->str_i] = '\0';
			data->token[data->j++].str = ft_strdup(data->str);
			data->str_i = 0;
		}
		data->i++;
		return (1);
	}
	if (ft_strchr("<>|&", data->c))
	{
		operator(data, rl);
		data->i++;
		return (1);
	}
	data->str[data->str_i++] = data->c;
	return (0);
}

static void	finalize_token(t_token_data *data, t_quote_tracker *qt)
{
	if (data->str_i > 0)
	{
		data->str[data->str_i] = '\0';
		data->token[data->j].str = ft_strdup(data->str);
		if (qt->active)
		{
			data->token[data->j].quote = qt->active;
			data->token[data->j].quote_start = qt->open_pos;
			data->token[data->j].quote_end = qt->current_len;
		}
		data->j++;
	}
}

void	token(char *rl, char **envp)
{
	t_token_data	data;
	t_quote_tracker	qt;

	if (!init_all(&data, rl))
		return ;
	init_quote_tracker(&qt);
	while (rl[data.i])
	{
		data.c = rl[data.i];
		if (handle_quotes(&data, &qt, rl[data.i + 1]))
			continue ;
		if (qt.active)
		{
			qt.current_len++;
			data.str[data.str_i++] = data.c;
			data.i++;
			continue ;
		}
		if (process_outside_quotes(&data, rl))
			continue ;
		data.i++;
	}
	finalize_token(&data, &qt);
	execution(data.token, data.size_token, envp);
	free_t(data.str, &data.token, data.size_token);
}
