/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <rmanzana@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:31:39 by rmanzana          #+#    #+#             */
/*   Updated: 2025/05/12 19:06:07 by rmanzana         ###   ########.fr       */
/*   Updated: 2025/02/05 15:06:51 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **cmd)
{
	int	i;
	int	is_n;
	int	j;

	i = 1;
	is_n = 0;
	if (cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n')
	{
		j = 2;
		while (cmd[i][j] != '\0')
		{
			if (cmd[i][j] != 'n')
			{
				is_n = 0;
				break ;
			}
			j++;
		}
		if (cmd[i][j] == '\0')
		{
			is_n = 1;
			i++;
		}
	}
	while (cmd[i])
	{
		if (cmd[i][0] != '\0')
			ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!is_n)
		write(1, "\n", 1);
}
