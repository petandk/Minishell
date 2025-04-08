/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <gpolo@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:02:01 by gpolo             #+#    #+#             */
/*   Updated: 2025/04/08 13:12:54 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int select_type(char *rl, t_shell **shell, char **envp)
{
	t_list	*list;
	char	*arg;

	if (!rl)
		return (1);
	else if (ft_strcmp(rl, "exit") == 0)
		return (ft_exit(shell, 0), 1);
	else if (ft_strncmp(rl, "echo", 4) == 0)
	{
		if (ft_strncmp(rl + 4, " -n", 3) == 0)
			ft_echo(rl, 1);
		else
			ft_echo(rl, 0);
	}
	else if (ft_strncmp(rl, "cd", 2) == 0)
		ft_cd(*shell, rl + 3);
	else if (ft_strncmp(rl, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(rl, "export", 6) == 0)
	{
		arg = rl + 6;
		while (*arg && ft_isspace(*arg))
			arg++;
		if (*arg)
			ft_export((*shell)->env, arg);
		else
			ft_export((*shell)->env, NULL);
	}
	else if (ft_strncmp(rl, "unset", 5) == 0)
	{
		arg = rl + 5;
		while (*arg && ft_isspace(*arg))
			arg++;
		if (*arg)
			ft_unset(&(*shell)->env, arg);
	}
	else if (ft_strncmp(rl, "env", 3) == 0)
		ft_env((*shell)->env);
	else if (ft_strstr(rl, "<<") != NULL)
	{
		list = ft_heredoc(rl);
		print_heredoc(list);
		ft_lstclear(&list, free);
	}
	else if (*rl)
	{
		token(rl, envp);
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
	if (!shell->env)
		return (free(shell), 1);
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
	free(shell);
	return (0);
	if (!argv)
		argc--;
}
