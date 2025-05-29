/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exapncion_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:22:44 by gpolo             #+#    #+#             */
/*   Updated: 2025/05/29 11:45:45 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_expan(char *str, int start, int qs, int qe)
{
	char	c;
	int		len;

	len = 0;
	if (str[start] == '?')
		return (1);
	while (str[start + len])
	{
		c = str[start + len];
		if (start + len == qs && start + len == qe)
			break ;
		if (start + len == qs || start + len == qe)
		{
			if (start + len == qe && (ft_isalnum(c) || c == '_'))
				len++;
			break ;
		}
		if (!ft_isalnum(c) && c != '_')
			break ;
		len++;
	}
	return (len);
}

static char	*find_value(char *key, t_env *env, int exst)
{
	t_env	*var;
	char	*value;

	if (!malloc_test((void *)key))
		exit(1);
	if (ft_strcmp(key, "?") == 0)
	{
		value = ft_itoa(exst);
		free(key);
		return (value);
	}
	var = find_env_var(env, key);
	free(key);
	if (var)
		value = ft_strdup(var->value);
	else
		value = "";
	return (value);
}

static void	process_dollar(t_expan *ex, char **str,
	t_quotes *quote, t_shell *shell)
{
	int		len;
	char	*value;
	char	*tmp;

	ex->start = ex->i + 1;
	while (quote[ex->j].quote_start != 0 || quote[ex->j].quote_end != 0)
	{
		if (ex->start < quote[ex->j].quote_end)
			break ;
		ex->j++;
	}
	len = len_expan(*str, ex->start,
			quote[ex->j].quote_start, quote[ex->j].quote_end);
	if (len == 0 && ft_strlen(*str) == 1 && quote[ex->j].quote == 0)
	{
		tmp = ft_substr(*str, ex->i, 1);
		ex->new_str = ft_strjoin_free(ex->new_str, tmp);
		free(tmp);
		ex->i++;
		return ;
	}
	value = find_value(ft_substr(*str, ex->start, len),
			shell->env, shell->exit_status);
	ex->new_str = ft_strjoin_doblefree(ex->new_str, value);
	ex->i += len + 1;
}

void	expan(char **str, t_quotes *quote, t_shell *shell)
{
	t_expan	ex;
	char	*tmp;

	ex.new_str = ft_strdup("");
	ex.i = 0;
	ex.j = 0;
	while ((*str)[ex.i])
	{
		if ((*str)[ex.i] == '$' && !is_in_single_quote(ex.i, quote))
			process_dollar(&ex, str, quote, shell);
		else
		{
			tmp = ft_substr(*str, ex.i, 1);
			ex.new_str = ft_strjoin_free(ex.new_str, tmp);
			free(tmp);
			ex.i++;
		}
	}
	free(*str);
	*str = ex.new_str;
}

void	expancion_var(t_comand_data *cmd, t_shell *shell)
{
	int	i;

	i = 0;
	while (cmd->comand && cmd->comand[i])
	{
		if (ft_strchr(cmd->comand[i], '$'))
			expan(&cmd->comand[i], cmd->quote[i], shell);
		i++;
	}
}
