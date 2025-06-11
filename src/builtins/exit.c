/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <rmanzana@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:56:33 by rmanzana          #+#    #+#             */
/*   Updated: 2025/06/10 18:26:08 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_no_print(t_shell **shell, int exit_code)
{
	if (!shell || !*shell)
		exit(exit_code & 0xFF);
	cleanup_shell(shell);
	exit (exit_code & 0xFF);
}

void	ft_exit(t_shell **shell, int exit_code)
{
	write(1, "exit\n", 5);
	ft_exit_no_print(shell, exit_code);
}
