/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <gpolo@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:02:01 by gpolo             #+#    #+#             */
/*   Updated: 2025/02/19 17:28:13 by rmanzana         ###   ########.fr       */
/*   Updated: 2025/02/05 20:16:45 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int select_type(char *rl, t_shell *shell)
{
	if (!rl)
		return (1);
	else if (ft_strcmp(rl, "exit") == 0)
		return (ft_exit(&shell), 1);
	else if (ft_strncmp(rl, "echo", 4) == 0)
		ft_echo(rl, 0);
	else if (ft_strncmp(rl, "cd", 2) == 0)
		ft_cd(shell, rl);
	else if (ft_strncmp(rl, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(rl, "export", 6) == 0)
		ft_export(shell->env);
	else if (*rl)
	{
		token(rl);
		add_history(rl);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*rl;
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	shell->prev_dir = NULL;
	shell->env = create_env_list(envp);
	while (1)
	{
		rl = readline(YELLOW "M" RED "i" YELLOW "n"
				RED "i" YELLOW "s" RED "h"
				YELLOW "e" RED "l" YELLOW "l" GREY " > " RESET);
		if (select_type(rl, shell))
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
