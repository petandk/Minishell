/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:17:55 by gpolo             #+#    #+#             */
/*   Updated: 2025/04/08 10:26:51 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	out_red(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("Error opening file\n");
		exit (1);
	}
	dup2(fd, 1);
	close (fd);
}

void	append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("Error opening file\n");
		exit (1);
	}
	dup2(fd, 1);
	close (fd);
}

void	in_red(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening file\n");
		exit (1);
	}
	dup2(fd, 0);
	close (fd);
}

void	here_doc(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	printf("WIP");
	if (fd < 0)
	{
		printf("Error opening file\n");
		exit (1);
	}
	dup2(fd, 0);
	close (fd);
}
