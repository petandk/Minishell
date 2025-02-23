/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:07:50 by gpolo             #+#    #+#             */
/*   Updated: 2025/02/23 16:15:55 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_comand(t_comand_data *comand, int num_comands)
{
	int i;
	int j;
 
	i = 0;
	if (!comand)
		return;
	while (i < num_comands)
	{
		j = 0;
		while (comand[i].comand[j])
		{
			free(comand[i].comand[j]);
			j++;
		}
		free(comand[i].comand);
		free(comand[i].quote);
		free(comand[i].in_file);
		free(comand[i].out_file);
		i++;
	}
	free(comand);
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

int    execution(t_token *token, int size_token, char  **envp)
{
	int				i;
	int				j;
	int				pipefd[2];
	pid_t			pid;
	int 			fd_in;
	int				fd;
	char			**args;
	t_comand_data	*comand;

	args = NULL;
	i = 0;
	fd_in = 0;
	fd = 0;
	int num_comands = prepare_to_execute(&comand, token, size_token);
	print_comands(comand, num_comands);
	free_comand(comand, num_comands);
/*	while (i < size_token)
	{
		j = 0;
		while (i + j < size_token && token[i + j].str && !token[i + j].pipe)
			j++;
		args = (char **)malloc((j + 1) * sizeof(char *));
		args[j] = NULL;
		j = 0;
		while (j < size_token && token[i].str && !token[i].pipe)
		{
			args[j] = ft_strdup(token[i].str);
			if (!args[j])
			{
				printf("error duplicacion de string");
				free_args(args);
				exit(1);
			}
			j++;
			i++;
		}
		print_args(args);
//------------------------------//
		if (i < size_token && token[i].pipe)
			pipe(pipefd);
		pid = fork();
		if (pid == 0)
		{
			if (fd_in != 0)
			{
				dup2(fd_in, 0);
				close(fd_in);
			}
			if (i < size_token && token[i].pipe)
			{
				dup2(pipefd[1], 1);
				close(pipefd[0]);
				close(pipefd[1]);
			}
			if (i + 1 < size_token)
			{
				if (token[i].greater_than)
				{
					fd = open(token[i + 1].str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
					if (fd < 0)
					{
						printf("Error opening file");
						exit (1);
					}
					dup2(fd, 1);
					close (fd);
					i++;
				}
				else if (token[i].double_greater)
				{
					fd = open(token[i + 1].str, O_WRONLY | O_CREAT | O_APPEND, 0644);
					if (fd < 0)
					{
						printf("Error opening file");
						exit (1);
					}
					dup2(fd, 1);
					close (fd);
					i++;
				}
				else if (token[i].less_than)
				{
					fd = open(token[i + 1].str, O_RDONLY);
					if (fd < 0)
					{
						printf("Error opening file");
						exit (1);
					}
					dup2(fd, 0);
					close (fd);
					i++;
				}
				else if (token[i].double_less)
				{
					printf("WORK IN PROGRES\n");
					i++;
				}
			}
			execute_command(args, envp);
			printf("execve error\n");
			exit(1);
		}
		else 
		{
			waitpid(pid, NULL, 0);
			free_args(args);
			if (i < size_token && token[i].pipe)
			{
				close(pipefd[1]);
				fd_in = pipefd[0];
			}
			else
				fd_in = 0;
		}
		i++;
	}*/
	return (1);
}
