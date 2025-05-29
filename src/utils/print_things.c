/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pirnt_things.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:17:24 by gpolo             #+#    #+#             */
/*   Updated: 2025/05/20 12:30:37 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_token_array(t_token *tokens, int size)
{
    int i;
    int q;

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
        printf("  quote_count: %d\n", tokens[i].quote_count);
        
        // Imprimir información de todos los quotes para este token
        q = 0;
        while (q < tokens[i].quote_count && q < 16)
        {
            printf("  Quote %d:\n", q);
            printf("    type: %s\n", 
                  tokens[i].quotes[q].quote == 1 ? "single" : 
                  tokens[i].quotes[q].quote == 2 ? "double" : "none");
            printf("    start: %d\n", tokens[i].quotes[q].quote_start);
            printf("    end: %d\n", tokens[i].quotes[q].quote_end);
            q++;
        }
        
        i++;
        if (i < size) printf("\n"); // Separador entre tokens
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
	int i = 0;
	while (i < num_comands)
	{
		printf(">>%d<<\n", i + 1);
		printf("Command %d:\n", i + 1);

		// Print arguments
		printf("  Arguments: ");
		if (!comand[i].comand)
			printf("(None)\n");
		else
		{
			int j = 0;
			while (comand[i].comand[j])
			{
				printf("[%s]", comand[i].comand[j]);

				if (comand[i].quote && comand[i].quote[j] && comand[i].quote_count)
				{
					int q = 0;
					while (q < comand[i].quote_count[j])
					{
						const char *type = comand[i].quote[j][q].quote == 1 ? "single" :
						                   comand[i].quote[j][q].quote == 2 ? "double" : "none";
						printf("(%s:%d-%d)", type,
							comand[i].quote[j][q].quote_start,
							comand[i].quote[j][q].quote_end);
						q++;
					}
				}
				j++;
			}
			printf("\n");
		}

		// Print input files
		printf("  Input files: ");
		if (comand[i].in_file && comand[i].in_count > 0)
		{
			for (int k = 0; k < comand[i].in_count; k++)
			{
				printf("%s%s", (k > 0) ? ", " : "", comand[i].in_file[k]);
			}
			printf("\n");
		}
		else
			printf("(None)\n");

		// Print output files
		printf("  Output files: ");
		if (comand[i].out_file && comand[i].out_count > 0)
		{
			for (int k = 0; k < comand[i].out_count; k++)
			{
				printf("%s%s", (k > 0) ? ", " : "", comand[i].out_file[k]);
			}
			printf("\n");
		}
		else
			printf("(None)\n");

		printf("\n");
		i++;
	}
}
