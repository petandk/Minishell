/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:47:53 by rmanzana          #+#    #+#             */
/*   Updated: 2025/04/14 20:56:03 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_chr_to_pipe_line(char *line, char c)
{
	char	*temp;

	temp = malloc(ft_strlen(line) + 2);
	if (!temp)
		return (free(line), NULL);
	ft_strlcpy(temp, line, ft_strlen(line) + 1);
	temp[ft_strlen(line)] = c;
	temp[ft_strlen(line) + 1] = '\0';
	free(line);
	return (temp);
}

char	*read_line_pipe(int fd)
{
	char	c;
	char	*line;
	int		ret;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	while (1)
	{
		ret = read(fd, &c, 1);
		if (ret <= 0)
			break ;
		if (c == '\n')
			return (line);
		line = add_chr_to_pipe_line(line, c);
		if (!line)
			return (NULL);
	}
	if (ret < 0 || (ret == 0 && *line == '\0'))
		return (free(line), NULL);
	return (line);
}

t_list	*read_heredoc_pipe(int fd)
{
	char	*line;
	t_list	*lines;

	lines = NULL;
	while (1)
	{
		line = read_line_pipe(fd);
		if (!line)
			break ;
		ft_lstadd_back(&lines, ft_lstnew(line));
	}
	return (lines);
}
