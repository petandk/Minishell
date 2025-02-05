/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <gpolo@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:02:01 by gpolo             #+#    #+#             */
/*   Updated: 2025/02/05 15:38:52 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int select_type(char *rl)
{
	if (!rl)
		return (1);
	if (ft_strcmp(rl, "exit") == 0)
		return (1);
	if (*rl)
	{
		token(rl);
		add_history(rl);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*rl;

	while (1)
	{
		rl = readline(YELLOW "M" RED "i" YELLOW "n"
				RED "i" YELLOW "s" RED "h"
				YELLOW "e" RED "l" YELLOW "l" GREY " > " RESET);
		if (select_type(rl))
		{
			free (rl);
			break ;	
		}
		free (rl);
	}
	return (0);
	if (!argv)
		argc--;
}
