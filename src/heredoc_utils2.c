/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:18:21 by rmanzana          #+#    #+#             */
/*   Updated: 2025/04/05 15:01:55 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_split_count(char **splited)
{
	int	i;

	i = 0;
	while (splited[i])
		i++;
	return (i);
}

void	handle_heredoc_signal(int signum)
{
	struct termios	term;
	struct termios	old_term;

	if (signum == SIGINT)
	{
		tcgetattr(STDIN_FILENO, &old_term);
		term = old_term;
		term.c_lflag &= ~(ECHOCTL);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		write(STDOUT_FILENO, "\n", 1);
		errno = EINTR;
		tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
	}
}
