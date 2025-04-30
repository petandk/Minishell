/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <rmanzana@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:31:39 by rmanzana          #+#    #+#             */
/*   Updated: 2025/04/26 15:37:37 by rmanzana         ###   ########.fr       */
/*   Updated: 2025/02/05 15:06:51 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char *msg, int is_n)
{
	if (msg && msg[0] != '\0')
	{
		while (*msg)
		{
			write(1, msg, 1);
			msg++;
		}
		if (!is_n)
			write(1, "\n", 1);
	}
	else
		write (1, "\n", 1);
}
