/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <rmanzana@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:02:01 by gpolo             #+#    #+#             */
/*   Updated: 2025/06/12 18:36:15 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_signal;

int	select_type(char *rl, t_shell **shell)
{
	if (!rl)
		ft_exit(shell, 1);
	else if (*rl)
	{
		token(rl, *shell);
		add_history(rl);
	}
	return (0);
}

static void	shell_loop(t_shell *shell)
{
	char	*rl;

	while (1)
	{
		rl = readline(YELLOW "M" RED "i" YELLOW "n"
				RED "i" YELLOW "s" RED "h"
				YELLOW "e" RED "l" YELLOW "l" GREY " > " RESET);
		if (select_type(rl, &shell))
		{
			free (rl);
			break ;
		}
		free (rl);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	signal (SIGINT, handle_sigint_main);
	signal (SIGQUIT, SIG_IGN);
	shell = shell_init(envp);
	shell_loop(shell);
	cleanup_shell(&shell);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	return (0);
}
