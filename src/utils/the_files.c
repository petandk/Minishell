/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:48:45 by gpolo             #+#    #+#             */
/*   Updated: 2025/06/03 14:29:07 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_quotes(t_token *tk, int index)
{
	if (!tk || !tk[index].str)
		return (0);
	return (tk[index].quote_count > 0);
}

void	process_redirection(t_token *tk, t_comand_data *cmd,
			int *idx, char *rdt)
{
	char	*str;

	str = NULL;
	if (tk[idx[2]].str == NULL && rdt)
	{
		if (ft_strcmp(rdt, "-") == 0)
		{
			if (has_quotes(tk, idx[2] + 1))
				str = init_str("_", tk, idx[2], idx[3]);
			else
				str = init_str("-", tk, idx[2], idx[3]);
		}
		else
			str = init_str(rdt, tk, idx[2], idx[3]);
		if (ft_strcmp(rdt, ">") == 0 || ft_strcmp(rdt, "_") == 0)
		{
			cmd->quote_out[idx[0]] = malloc(sizeof(t_quotes) * 16);
			ft_memcpy(cmd->quote_out[idx[0]],tk[idx[2] + 1].quotes,
				sizeof(t_quotes) * tk[idx[2] + 1].quote_count);
			cmd->quote_out_count[idx[0]] = tk[idx[2] + 1].quote_count;
			in_out_file(&cmd->out_file[idx[0]++], str);
		//	cmd->quote_out[idx[0]] == tk->quotes;
		}
		else
		{
			cmd->quote_in[idx[0]] = malloc(sizeof(t_quotes) * 16);
			ft_memcpy(cmd->quote_in[idx[1]], tk[idx[2] + 1].quotes,
				sizeof(t_quotes) * tk[idx[2] + 1].quote_count);
			cmd->quote_in_count[idx[1]] = tk[idx[2] + 1].quote_count;
			in_out_file(&cmd->in_file[idx[1]++], str);
		//	cmd->quote_out[idx[1]] == tk->quotes;
		}
		free(str);
	}
}

int	the_files(t_ind *ind, int size, t_token *tk, t_comand_data **cmd)
{
	int		idx[4];

	idx[0] = 0;
	idx[1] = 0;
	idx[3] = size;
	in_out_size(&(*cmd)[ind->j], *ind, size, tk);
	init_int_out(&(*cmd)[ind->j], (*cmd)[ind->j].in_count,
		(*cmd)[ind->j].out_count);
	while (ind->i < size && !tk[ind->i].pipe)
	{
		if (!tk[ind->i].str && ind->i + 1 < size && tk[ind->i + 1].str)
		{
			idx[2] = ind->i;
			if (tk[ind->i].greater_than)
				process_redirection(tk, &(*cmd)[ind->j], idx, ">");
			else if (tk[ind->i].double_greater)
				process_redirection(tk, &(*cmd)[ind->j], idx, "_");
			else if (tk[ind->i].less_than)
				process_redirection(tk, &(*cmd)[ind->j], idx, "<");
			else if (tk[ind->i].double_less)
				process_redirection(tk, &(*cmd)[ind->j], idx, "-");
		}
		ind->i++;
	}
	return (1);
}
