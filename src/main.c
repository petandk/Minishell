/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <rmanzana@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:02:01 by gpolo             #+#    #+#             */
/*   Updated: 2025/06/14 10:22:16 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal;

static void	ft_a(t_shell **shell, int exit_code)
{
	if (!shell || !*shell)
		return ;
	if ((*shell)->env)
		clear_env_list(&(*shell)->env);
	free(*shell);
	*shell = NULL;
	exit (exit_code & 0xFF);
}

int	select_type(char *rl, t_shell **shell)
{
	if (!rl)
	{
		if (*shell)
			ft_a(shell, 0);
		ft_exit(shell, 1);
	}
	else if (*rl)
	{
		token(rl, *shell);
		if (isatty(STDIN_FILENO))
			add_history(rl);
	}
	return (0);
}

static void	shell_loop(t_shell *shell)
{
	char	*rl;
	char	*prompt;

	if (isatty(STDIN_FILENO))
	{
		prompt = YELLOW "M" RED "i" YELLOW "n" RED "i" YELLOW "s" \
			RED "h" YELLOW "e" RED "l" YELLOW "l" GREY " > " RESET;
	}
	else
		prompt = "";
	while (1)
	{
		rl = readline(prompt);
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
	shell_signals();
	shell = shell_init(envp);
	shell_loop(shell);
	cleanup_shell(&shell);
	child_execution_signals();
	return (0);
}
