/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exapncion_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:22:44 by gpolo             #+#    #+#             */
/*   Updated: 2025/05/13 17:26:46 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int len_expan(char *str ,int start, int qs, int qe)
{
	char	c;
	int		len;
 
	len = 0;
	while (str[start + len])
	{
		c = str[start + len];
		if (qe > qs && (start + len == qs || start + len == qe))
			break;
		if (!ft_isalnum(c) && c != '_')
			break;
		len++;
	}
	return (len);
}

static char	*find_value(char *key, t_env *env)
{
	t_env   *var;
	char    *value;

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

static char *replace_str(char *str1, int start, int end, char *str2)
{
	int new_len;
	char *new_str;
	int i;
	int j;

	new_len = ft_strlen(str1 - (end - start)) + ft_strlen(str2);
	new_str = malloc(new_len + 1);
	if (!malloc_test((void *)new_str))
		exit(1);
	i = 0;
	while (i < start)
	{
		new_str[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2 && str2[j])
		new_str[i++] = str2[j++];
	j = end;
	while (str1[j])
		new_str[i++] = str1[j++];
	new_str[i] = '\0';
	return (new_str);
}

void expan(char **str, t_quotes *quote, t_env *env)
{
	char	*new_str;
	char	*value;
	int		len;
	int		start;
	int		i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && quote->quote != 1)
		{
			start = (i + 1);
			len = len_expan(*str, start,quote->quote_start,quote->quote_end);
			if (len == 0)
			{
				i++;
				continue ;
			}
			value = find_value(ft_substr(*str, start, len), env);
			new_str = replace_str(*str, i, start + len, value);
			free(*str);
			(*str) = new_str;
			i += ft_strlen(value) - 1;
		}
		i++;
	}
}

void	expancion_var(t_comand_data *cmd, t_env *env)
{
	int i;

	i = 0;
	while (cmd->comand && cmd->comand[i])
	{
		if (ft_strchr(cmd->comand[i], '$'))
			expan(&cmd->comand[i], cmd->quote[i], env);
		i++;
	}
}
