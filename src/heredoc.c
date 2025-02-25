/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:19:34 by rmanzana          #+#    #+#             */
/*   Updated: 2025/02/25 18:41:45 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	if (!*needle)
		return ((char *) haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (needle[j] && haystack[i +j] == needle[j])
			j++;
		if (!needle[j])
			return ((char *) &haystack[i]);
		i++;
	}
	return (NULL);
}
static char	*ft_replace(const char *str)
{
	size_t	size;
	char	*result;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	size = ft_strlen(str);
	if (ft_strstr(str, " << "))
		size -= 3;
	else if (ft_strstr(str, "<<"))
		size -= 1;
	result = (char *)malloc(size + 1 * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] == '<' && str[i + 2] == '<' && str[i + 3] == ' ')
		{
			result[j]='<';
			i += 4;
			j++;
			continue;
		}
		else if (str[i] == '<' && str[i + 1] == '<')
		{
			result[j] = '<';
			i += 2;
			j++;
			continue;
		}
		result [j] = str[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}

void	ft_heredoc(char *input)
{
	char	**splited;
	char	*nl;
	char	*aux;
	int		i;
	int		num_brackets;

	if (ft_strstr(input, "<<") != NULL)
	{
		aux = ft_replace(input);
		splited = ft_split(aux, '<');
		if (splited && !splited[0])
			return (free(splited));
		while (1)
		{
			nl = readline("> ");
			if (nl == NULL)
				break ;
			printf("aux is %s\nEOF is: %s and yu said %s\n", aux, splited[1], nl);
			i = 1;
			while (splited[i])
				printf("%s\n", splited[i++]);
			if (splited && splited[1] && ft_strcmp(splited[1], nl) == 0)
			{
				free(nl);
				break;
			}
			free(nl);
		}
		if (splited)
			free_split(splited, -1);
	}
}
