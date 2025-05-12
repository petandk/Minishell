/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <gpolo@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:18:35 by gpolo             #+#    #+#             */
/*   Updated: 2025/05/12 11:51:45 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_quotes(t_token_data *data, t_quote_tracker *qt)
{
	t_token	*curr_token;

	curr_token = &data->token[data->j];
	if ((data->c == '\'' && qt->active != 2)
		|| (data->c == '\"' && qt->active != 1))
	{
		if (!qt->active)
			start_quote(data, qt, curr_token);
		else
			end_quote(data, qt, curr_token);
		data->i++;
		return (1);
	}
	return (0);
}

static void	save_token_string(t_token_data *data)
{
	if (data->str_i > 0)
	{
		data->str[data->str_i] = '\0';
		data->token[data->j].str = ft_strdup(data->str);
		data->j++;
		data->str_i = 0;
	}
}

static void	handle_operator(t_token_data *data, char *rl)
{
	save_token_string(data);
	if ((data->c == '>' && rl[data->i + 1] == '>')
		|| (data->c == '<' && rl[data->i + 1] == '<'))
	{
		token_operator(&data->token[data->j], data->c, rl[data->i + 1]);
		data->j++;
		data->i++;
	}
	else
	{
		token_operator(&data->token[data->j], data->c, '\0');
		data->j++;
	}
}

static int	process_outside_quotes(t_token_data *data, char *rl)
{
	if (ft_isspace(data->c))
	{
		save_token_string(data);
		data->i++;
		return (1);
	}
	if (ft_strchr("<>|&", data->c))
	{
		handle_operator(data, rl);
		data->i++;
		return (1);
	}
	data->str[data->str_i] = data->c;
	data->str_i++;
	return (0);
}

void	token(char *rl, t_env *env, char **envp)
{
	t_token_data	data;
	t_quote_tracker	qt;

	if (!init_all(&data, rl))
		return ;
	init_quote_tracker(&qt);
	while (rl[data.i])
	{
		data.c = rl[data.i];
		if (handle_quotes(&data, &qt))
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
	if (!finalize_token(&data))
		execution(data.token, data.size_token, env, envp);
	free_t(data.str, &data.token, data.size_token);
}
