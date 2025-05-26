/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:59:59 by gpolo             #+#    #+#             */
/*   Updated: 2025/05/26 13:57:50 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int len_expan(char *str, int start)
{
	char	c;
	int		len;

	len = 0;
	while (str[start + len])
	{
		c = str[start + len];
		if (ft_isalnum(c) || c == '_')
			len++;
		else
			break ;
	}
	return (len);
}

static char	*find_value(char *key, t_env *env)
{
	t_env	*var;
	char	*value;

	if (!malloc_test((void *)key))
		exit(1);
	var = find_env_var(env, key);
	free(key);
	if (var)
		value = var->value;
	else
		value = "";
	return (value);
}


char *heredoc_expansion(char *str, t_shell **shell)
{
	int		i;
	int		len;
	int		start;
	char	*value;
	char	*tmp;
	char	*new_str;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			start = i + 1;
			len = len_expan(str, start);
			if (len == 0)
			{
				i++;
				continue ;
			}
			value = find_value(ft_substr(str, start, len), (*shell)->env);
			tmp = ft_substr(str, 0, i);
			new_str = ft_strjoin_free(tmp, value);
			tmp = ft_strdup(str + start + len);
			new_str = ft_strjoin_free(new_str, tmp);
			free(tmp);
			i += ft_strlen(value);
		}
		else 
			i++;
	}
	return (new_str);
}
