/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:34:48 by gpolo             #+#    #+#             */
/*   Updated: 2025/02/23 15:16:37 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_quote_c(char *rl, t_quote *quote, int *tokens, int *i)
{
	if (rl[*i] == '\'' && !quote->in_double)
	{
		quote->in_single = !quote->in_single;
		if (quote->in_single == 0)
			*tokens += 1;
		*i += 1;
		return (1);
	}
	else if (rl[*i] == '\"' && !quote->in_single)
	{
		quote->in_double = !quote->in_double;
		if (quote->in_double == 0)
			*tokens += 1;
		*i += 1;
		return (1);
	}
	return (0);
}

int	quak(int current,int next)
{
	if ((current == '>' && next == '>') || (current == '<' && next == '<'))
		return (1);
	return (0);
}

int	out_quote_c(char *rl, int *tokens, int *i)
{
	if (ft_isspace(rl[*i]))
	{
		while (rl[*i] && ft_isspace(rl[*i]))
			*i += 1;
		return (1);
	}
	if (ft_strchr("<>|", rl[*i]))
	{
		if (quak(rl[*i], rl [*i + 1]))
		{
			if (rl[*i + 2] == rl[*i])
				return (-1);
			*i += 1;
		}
		*i += 1;
		*tokens += 1;
	}
	else if (rl[*i])
	{
		*tokens += 1;
		while (rl[*i] && !ft_isspace(rl[*i]) && !ft_strchr("<>|", rl[*i]))
			*i += 1;
		return (1);
	}
	return (0);
}

int	count_tokens(char *rl)
{
	int		i;
	int		tokens;
	int		res;
	t_quote	quote;

	i = 0;
	quote = (t_quote){.in_single = 0, .in_double = 0};
	tokens = 0;
	while (rl[i])
	{
		if (in_quote_c(rl, &quote, &tokens, &i))
			continue ;
		if (!quote.in_single && !quote.in_double)
		{
			res = out_quote_c(rl, &tokens, &i);
			if (res < 0)
				return (-1);
			if (res)
				continue ;
		}
		else
			i++;
	}
//	printf("tokens -> %d\n", tokens);
	return (tokens);
}
