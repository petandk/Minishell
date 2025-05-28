/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:59:59 by gpolo             #+#    #+#             */
/*   Updated: 2025/05/28 13:04:54 by gpolo            ###   ########.fr       */
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

char	*ft_strjoin_doblefree(char *s1, char *s2)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (join);
}

char *heredoc_expansion(char *str, t_shell **shell)
{
	int		i;
	int		len;
	char	*value;
	char	*tmp;
	char	*new_str;
	char	*key;

	i = 0;
	new_str = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			len = len_expan(str, i + 1);
			if (len == 0)
			{
				tmp = ft_strdup("$");
				new_str = ft_strjoin_doblefree(new_str, tmp);
				i++;
				continue ;
			}
			key = ft_substr(str, i + 1, len);
			value = find_value(key, (*shell)->env);
			tmp = ft_strdup(value);
			new_str = ft_strjoin_doblefree(new_str, tmp);
			i += len + 1;
		}
		else
		{
			tmp = ft_substr(str, i, 1);
			new_str = ft_strjoin_doblefree(new_str, tmp);
			i++;
		}
	}
	return (new_str);
}
