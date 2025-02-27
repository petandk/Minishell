/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pirnt_things.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:17:24 by gpolo             #+#    #+#             */
/*   Updated: 2025/02/27 15:20:26 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_array(t_token *tokens, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("Token %d:\n", i);
		printf("  str: %s\n", tokens[i].str);
		printf("  greater_than: %d\n", tokens[i].greater_than);
		printf("  double_greater: %d\n", tokens[i].double_greater);
		printf("  less_than: %d\n", tokens[i].less_than);
		printf("  double_less: %d\n", tokens[i].double_less);
		printf("  pipe: %d\n", tokens[i].pipe);
		printf("  quote: %d\n", tokens[i].quote);
		i++;
	}
}

void	print_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		printf("args[%d]->%s\n",i, args[i]);
		i++;
	}
}

void print_comands(t_comand_data *comand, int num_comands)
{
    int i, j;

    if (!comand)
    {
        printf("No commands to print.\n");
        return;
    }

    i = 0;
    while (i < num_comands)
    {
        printf("Command %d:\n", i + 1);
        
        j = 0;
        if (comand[i].comand)
        {
            printf("  Arguments: ");
            while (comand[i].comand[j])
            {
                printf("[%s]", comand[i].comand[j]);
                if (comand[i].quote && comand[i].quote[j])
                    printf("(quote:%d) ", comand[i].quote[j]);
                j++;
            }
            printf("\n");
        }
        else
            printf("  Arguments: (None)\n");

        printf("  Input file: %s\n", comand[i].in_file ? comand[i].in_file : "(None)");
        printf("  Output file: %s\n", comand[i].out_file ? comand[i].out_file : "(None)");

        i++;
    }
}

