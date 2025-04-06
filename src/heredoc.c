/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:19:34 by rmanzana          #+#    #+#             */
/*   Updated: 2025/04/06 17:05:01 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_line(char *line, char *delimiter, t_list **lines)
{
	if (!line)
		return (1);
	if (ft_strcmp(delimiter, line) == 0)
		return (free(line), 2);
	ft_lstadd_back(lines, ft_lstnew(ft_strdup(line)));
	free(line);
	return (0);
}

static void	ft_process_heredoc(char	*delimiter, t_list **lines)
{
	char	*line;
	int		result;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			control_d_error(delimiter);
			break ;
		}
		result = process_line(line, delimiter, lines);
		if (result != 0)
			break ;
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
	errno = 0;
	while (i <= aux->num_brackets)
	{
		if (lines)
			ft_lstclear(&lines, free);
		lines = NULL;
		ft_process_heredoc(splited[i], &lines);
		if (!lines && errno == EINTR)
			break;
		i++;
	}
	clean_heredoc(aux);
	if (splited)
		free_split(splited, -1);
	return (lines);
}
