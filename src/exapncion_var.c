/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exapncion_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:22:44 by gpolo             #+#    #+#             */
/*   Updated: 2025/05/17 14:44:08 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int len_expan(char *str ,int start, int qs, int qe)
{
	char	c;
	int		len;
 
	len = 0;
	printf("_____LEN_EXPAN____\n");
	printf("qs-> %d:\n",qs);
	printf("qe-> %d:\n",qe);
	printf("start-> %d:\n",start);
	while (str[start + len])
	{
		printf("start + len-> %d:\n",start + len);
		c = str[start + len];
		printf("C-> %c:\n",c);
		if (start + len == qs && start + len == qe)
			break;
		if (start + len == qs || start + len == qe)
		{
			if (start + len == qe && (ft_isalnum(c) || c == '_'))
				len++;
			break;
		}
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
	printf("value to expan-> %s:\n",key);
	var = find_env_var(env, key);
	free(key);
	if (var)
		value = var->value;
	else
		value = "";
	return (value);
}
/*
static char *replace_str(char *str1, int start, int end, char *str2)
{
	int new_len;
	char *new_str;
	int i;
	int j;
	
	printf("str1 -> %s\n",str1);
	printf("str2 -> %s\n",str2);
	new_len = ft_strlen(str1) - (end - start) + ft_strlen(str2);
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
}*/


void expan(char **str, t_quotes *quote, t_env *env)
{
	char	*new_str;
	char	*value;
	char	*tmp;
	int		len;
	int		start;
	int		i;
	int 	j;

	new_str = ft_strdup("");
	i = 0;
	j = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && quote[j].quote != 1)
		{
			start = (i + 1);
			while ((quote[j].quote_end && start > quote[j].quote_end)
				&&(quote[j].quote_start != 0 && quote[j].quote_end != 0))
				j++;
			len = len_expan(*str, start,quote[j].quote_start,quote[j].quote_end);
			printf("len-> %d:\n",len);
			if (len == 0 && (ft_strlen(*str) == 1) && (quote[j].quote == 0))
			{
				tmp = ft_substr(*str, i, 1);
				new_str = ft_strjoin_free(new_str, tmp);
				free(tmp);
				i++;
				continue ;
			}
			value = find_value(ft_substr(*str, start, len), env);
			printf("value -> %s:\n",value);
			new_str=ft_strjoin_free(new_str, value);
			printf("value to replace-> %s:\n",new_str);
			printf("_____________________\n");
			i +=(len + 1);
		}
		else 
		{
			tmp = ft_substr(*str, i, 1);
			new_str = ft_strjoin_free(new_str, tmp);
			free(tmp);
			i++;
		}
	}
	free(*str);
	(*str) = new_str;
	printf("the str repalced-> %s:\n",(*str));
	printf("_____________________\n");
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
