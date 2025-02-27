/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <gpolo@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:18:35 by gpolo             #+#    #+#             */
/*   Updated: 2025/02/27 14:36:42 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_quote(t_token_data *data)
{
	if (data->c == '\'' && !data->in_double_quotes)
	{
		data->in_quotes = !data->in_quotes;
		data->token[data->j].quote = 1;
		data->i++;
		return (1);
	}
	else if (data->c == '\"' && !data->in_quotes)
	{
		data->in_double_quotes = !data->in_double_quotes;
		data->token[data->j].quote = 2;
		data->i++;
		return (1);
	}
	return (0);
}

void	operator(t_token_data *data, char *rl)
{
	if (data->str_i > 0)
	{
		data->str[data->str_i] = '\0';
		data->token[data->j++].str = ft_strdup(data->str);
//		printf("Token: %s\n", data->str);
		data->str_i = 0;
	}
	if ((data->c == '>' && rl[data->i + 1] == '>')
		|| (data->c == '<' && rl[data->i + 1] == '<'))
	{
		token_operator(&data->token[data->j++], data->c, rl[data->i + 1]);
//		printf("operator: %c%c\n", data->c, rl[data->i + 1]);
		data->i++;
	}
	else
	{
		token_operator(&data->token[data->j++], data->c, '\0');
//		printf("operator: %c\n", data->c);
	}
}

int	out_quotes(t_token_data *data, char *rl)
{
	if (ft_isspace(data->c))
	{
		if (data->str_i > 0)
		{
			data->str[data->str_i] = '\0';
			data->token[data->j++].str = ft_strdup(data->str);
//			printf("Token: %s\n", data->str);
			data->str_i = 0;
		}
		data->i++;
		return (1);
	}
	if (ft_strchr("<>|", data->c))
	{
		operator(data, rl);
		data->i++;
		return (1);
	}
	data->str[data->str_i++] = data->c;
	return (0);
}

void	str_index(t_token_data *data)
{
	if (data->str_i > 0)
	{
		data->str[data->str_i] = '\0';
		data->token[data->j++].str = ft_strdup(data->str);
//		printf("Token: %s\n", data->str);
	}
}

void	token(char *rl)
{
	t_token_data	data;

	if (!init_all(&data, rl))
		return ;
	while (rl[data.i])
	{
		data.c = rl[data.i];
		if (in_quote(&data))
			continue ;
		if (!data.in_quotes && !data.in_double_quotes)
		{
			if (out_quotes(&data, rl))
				continue ;
		}
		else
			data.str[data.str_i++] = data.c;
		data.i++;
	}
	str_index(&data);
//	print_token_array(data.token, data.size_token);
//	execution(data.token, data.size_token, envp);
	free (data.str);
	free_token(&data.token, data.size_token);
}
