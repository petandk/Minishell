/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   borrar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:20:27 by rmanzana          #+#    #+#             */
/*   Updated: 2025/02/27 14:40:30 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_heredoc(t_list *list)
{
	t_list	*current;

	if (!list)
		return ;
	current = list;
	while (current != NULL)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
}
