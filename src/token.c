/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <gpolo@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:18:35 by gpolo             #+#    #+#             */
/*   Updated: 2025/02/04 15:51:03 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenization(char **str, char **envp)
{
	int		i;
	char	**all_path;
	char    *path;

	i = find_path_index(envp);
	all_path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (str[i])
	{
		if (str && str[0] && str[i][0] != '/')
		{
			path = find_path_access(all_path, str);
			if (!path)
			{
				free_args(all_path);
				return ;
			}
			printf("%s -> es un comando\n",str[i]);
		}
		else if (str[i][0] == '/')
			printf("%s -> es un comando\n",str[i]);
		else if (str[i][0] == '-')	
			printf("%s -> es un un argumento\n",str[i]);
		else 
			printf("%s -> es texto\n",str[i]);
	}	
}

void	token(char *rl, char **envp)
{
	char **str;

	str = ft_split(rl, ' ');
	if (!str)
		return ;
	tokenization(str, envp);
	exit (1);
}
