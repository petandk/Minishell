/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <gpolo@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:02:01 by gpolo             #+#    #+#             */
/*   Updated: 2025/01/23 16:54:31 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int select_type(char *rl, char **envp)
{
	if (ft_strcmp(rl, "exit") == 0)
	{
		rl_clear_history();
		return (1);
	}
	else if (*rl)
	{
		reed_rl(rl, envp);
		add_history(rl);
//		printf("%s\n", rl);
		return (0);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*rl;

/*	rl = readline(YELLOW "M" RED "i" YELLOW "n"
				RED "i" YELLOW "s" RED "h"
				YELLOW "e" RED "l" YELLOW "l" GREY " > " RESET);i*/
	while (1)
	{
		rl = readline(YELLOW "M" RED "i" YELLOW "n"
				RED "i" YELLOW "s" RED "h"
				YELLOW "e" RED "l" YELLOW "l" GREY " > " RESET);
/*		if (*rl == '\0')
		{
			free (rl);
			continue ;
		}
		if (*rl)
			add_history(rl);*/
		if (select_type(rl, envp))
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
