/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:07:50 by gpolo             #+#    #+#             */
/*   Updated: 2025/05/06 11:28:36 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_string_array(char **array, int count)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (i < count && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_comand(t_comand_data *comand, int num_comands)
{
	int	i;
	int	j;

	i = 0;
	if (!comand)
		return ;
	while (i < num_comands)
	{
		j = 0;
		while (comand[i].comand && comand[i].comand[j])
			free(comand[i].comand[j++]);
		j = 0;	
		while (comand[i].quote && comand[i].quote[j] && (j < 16))
			free(comand[i].quote[j++]);
		free(comand[i].comand);
		free(comand[i].quote);
		free(comand[i].quote_count);
		free_string_array(comand[i].in_file, comand[i].in_count);
		free_string_array(comand[i].out_file, comand[i].out_count);
		i++;
	}
	free(comand);
}

int	execution(t_token *token, int size_token, t_shell *shell, char **envp)
{
	t_comand_data	*comand;
	int				num_comands;

	num_comands = prepare_to_execute(&comand, token, size_token);
	if (num_comands <= 0)
		return (-1);
	print_comands(comand, num_comands);
	printf("___________________________EXECUTION___________________________\n");
	execute_pipeline(comand, num_comands, shell, envp);
	free_comand(comand, num_comands);
	return (1);
}
