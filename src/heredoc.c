/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:19:34 by rmanzana          #+#    #+#             */
/*   Updated: 2025/02/27 14:40:50 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_split_count(char **splited)
{
	int	i;

	i = 0;
	while (splited[i])
		i++;
	return (i);
}

static void	clean_heredoc(t_heredoc *vars)
{
	if (!vars)
		return ;
	if (vars->helper)
		free(vars->helper);
	if (vars->line)
		free(vars->line);
	free(vars);
}

static void	ft_process_heredoc(char	*delimiter, t_list **lines)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(delimiter, line) == 0)
		{
			free(line);
			break ;
		}
		ft_lstadd_back(lines, ft_lstnew(ft_strdup(line)));
		free(line);
	}
}

static char	**ft_setup_heredoc(char *input, t_heredoc **here)
{
	char	**splited;

	*here = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (!here)
		return (NULL);
	(*here)->helper = ft_replace(input);
	(*here)->line = NULL;
	splited = ft_split((*here)->helper, '<');
	if (splited && !splited[0])
	{
		clean_heredoc(*here);
		free(splited);
		return (NULL);
	}
	(*here)->num_brackets = ft_split_count(splited) - 1;
	return (splited);
}

t_list	*ft_heredoc(char *input)
{
	char		**splited;
	t_list		*lines;
	t_heredoc	*aux;
	int			i;

	lines = NULL;
	if (ft_strstr(input, "<<") == NULL)
		return (NULL);
	splited = ft_setup_heredoc(input, &aux);
	if (!splited)
		return (NULL);
	i = 1;
	while (i <= aux->num_brackets)
	{
		if (lines)
			ft_lstclear(&lines, free);
		lines = NULL;
		ft_process_heredoc(splited[i], &lines);
		i++;
	}
	clean_heredoc(aux);
	if (splited)
		free_split(splited, -1);
	return (lines);
}
