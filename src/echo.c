/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <rmanzana@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:31:39 by rmanzana          #+#    #+#             */
/*   Updated: 2025/02/21 17:54:51 by rmanzana         ###   ########.fr       */
/*   Updated: 2025/02/05 15:06:51 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char *msg, int is_n)
{
	msg += 5;
	while (*msg)
	{
		write(1, msg, 1);
		msg++;
	}
	if (!is_n)
		write(1, "\n", 1);
}
/*
int	main(void)
{
	ft_echo("simulating -n", 1);
	ft_echo("simulating no -n", 0);
	return (0);
}
*/
