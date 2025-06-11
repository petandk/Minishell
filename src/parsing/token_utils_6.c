/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:01:55 by gpolo             #+#    #+#             */
/*   Updated: 2025/06/09 10:51:10 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_quotes(char *str)
{
	int		i;
	int		q;
	char	in_quote;

	in_quote = 0;
	i = 0;
	q = 0;
	while (str[i])
	{
		if ((str[i] == '\'') || (str[i] == '"'))
		{
			if (!in_quote)
			{
				in_quote = str[i];
				q++;
			}
			else if (in_quote == str[i])
			{
				in_quote = 0;
				q++;
			}
		}
		i++;
	}
	if ((q % 2) > 0)
		return (q / 2 + 1);
	return (q / 2);
}
