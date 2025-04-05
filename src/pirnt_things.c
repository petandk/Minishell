/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pirnt_things.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:17:24 by gpolo             #+#    #+#             */
/*   Updated: 2025/04/05 10:49:47 by gpolo            ###   ########.fr       */
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
		printf("  quote_start: %d\n", tokens[i].quote_start);
		printf("  quote_end: %d\n", tokens[i].quote_end);
		i++;
	}
}

void	print_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		printf("args[%d]->%s\n", i, args[i]);
		i++;
	}
}

void print_comands(t_comand_data *comand, int num_comands)
{
	int i, j, k;

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
				if (comand[i].quote && comand[i].quote[j].quote)
					printf("(quote:%d, start:%d, end:%d) ", 
						   comand[i].quote[j].quote,
						   comand[i].quote[j].quote_start,
						   comand[i].quote[j].quote_end);
				j++;
			}
			printf("\n");
		}
		else
			printf("  Arguments: (None)\n");

		if (comand[i].in_file && comand[i].in_count > 0)
		{
			printf("  Input files (%d):\n", comand[i].in_count);
			for (k = 0; k < comand[i].in_count; k++)
			{
				printf("    %d: %s", k + 1, comand[i].in_file[k]);
				if (comand[i].quote && comand[i].quote[j + k].quote)
					printf(" (quote:%d, start:%d, end:%d)", 
						   comand[i].quote[j + k].quote,
						   comand[i].quote[j + k].quote_start,
						   comand[i].quote[j + k].quote_end);
				printf("\n");
			}
		}
		else
			printf("  Input files: (None)\n");

		if (comand[i].out_file && comand[i].out_count > 0)
		{
			printf("  Output files (%d):\n", comand[i].out_count);
			for (k = 0; k < comand[i].out_count; k++)
			{
				printf("    %d: %s", k + 1, comand[i].out_file[k]);
				if (comand[i].quote && comand[i].quote[j + comand[i].in_count + k].quote)
					printf(" (quote:%d, start:%d, end:%d)", 
						   comand[i].quote[j + comand[i].in_count + k].quote,
						   comand[i].quote[j + comand[i].in_count + k].quote_start,
						   comand[i].quote[j + comand[i].in_count + k].quote_end);
				printf("\n");
			}
		}
		else
			printf("  Output files: (None)\n");
		i++;
	}
}
/*
void	print_comands(t_comand_data *comand, int num_comands)
{
	int i, j, k;

	if (!comand)
	{
		printf("No commands to print.\n");
		return ;
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
		if (comand[i].in_file && comand[i].in_count > 0)
		{
			printf("  Input files (%d):\n", comand[i].in_count);
			for (k = 0; k < comand[i].in_count; k++)
			{
				printf("	%d: %s\n", k + 1, comand[i].in_file[k]);
			}
		}
		else
			printf("  Input files: (None)\n");
		if (comand[i].out_file && comand[i].out_count > 0)
		{
			printf("  Output files (%d):\n", comand[i].out_count);
			for (k = 0; k < comand[i].out_count; k++)
			{
				printf("	%d: %s\n", k + 1, comand[i].out_file[k]);
			}
		}
		else
			printf("  Output files: (None)\n");
		i++;
	}
}*/
