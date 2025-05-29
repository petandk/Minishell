/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <rmanzana@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:41:32 by rmanzana          #+#    #+#             */
/*   Updated: 2025/05/29 17:40:01 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	*current;

	current = getcwd(NULL, 0);
	if (!current)
	{
		perror("pwd");
		shell->exit_status = 1;
		return ;
	}
	printf("%s\n", current);
	free(current);
	shell->exit_status = 0;
}
