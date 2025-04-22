/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <gpolo@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:02:01 by gpolo             #+#    #+#             */
/*   Updated: 2025/04/22 21:37:27 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	select_type(char *rl, t_shell **shell, char **envp)
{
	t_list	*list;

	if (!rl)
		return (printf("exit\n"), 1);
	else if (ft_strstr(rl, "<<") != NULL)
	{
		list = ft_heredoc(rl);
		print_heredoc(list);
		ft_lstclear(&list, free);
	}
	else if (*rl)
	{
		token(rl, *shell, envp);
		add_history(rl);
	}
	return (0);
}

static t_shell	*shell_init(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		exit (1);
	shell->prev_dir = NULL;
	shell->env = create_env_list(envp);
	if (!shell->env)
	{
		free(shell);
		exit (1);
	}
	return (shell);
}

static void	shell_loop(t_shell *shell, char **envp)
{
	char	*rl;

	while (1)
	{
		rl = readline(YELLOW "M" RED "i" YELLOW "n"
				RED "i" YELLOW "s" RED "h"
				YELLOW "e" RED "l" YELLOW "l" GREY " > " RESET);
		if (select_type(rl, &shell, envp))
		{
			free (rl);
			break ;
		}
		free (rl);
	}
}

static void	handle_sigint_main(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	signal (SIGINT, handle_sigint_main);
	signal (SIGQUIT, SIG_IGN);
	shell = shell_init(envp);
	shell_loop(shell, envp);
	free(shell);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	return (0);
}
