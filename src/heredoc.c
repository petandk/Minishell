/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:19:34 by rmanzana          #+#    #+#             */
/*   Updated: 2025/04/08 16:28:30 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_line(char *line, char *delimiter, int pipe_fd)
{
	if (!line)
		return (1);
	if (ft_strcmp(delimiter, line) == 0)
		return (free(line), 2);
	write(pipe_fd, line, ft_strlen(line));
	write(pipe_fd, "\n", 1);
	free(line);
	return (0);
}


static void sigint_handler(int sig)
{
	(void)sig;
	exit(130);
}

static void	child_process_heredoc(char	*delimiter, int pipe_fd)
{
	char	*line;
	int		result;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");	
		result = process_line(line, delimiter, pipe_fd);
		if (result == 1)
		{
			control_d_error(delimiter);
			break ;
		}
		else if (result == 2)
			break ;
	}
	close(pipe_fd);
	exit(EXIT_SUCCESS);
}

static char	*read_line_pipe(int fd)
{
	char	c;
	char	*line;
	char	*temp;
	int		ret;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	while(1)
	{
		ret = read(fd, &c, 1);
		if (ret <= 0)
			break ;
		if (c == '\n')
			return (line);
		temp = malloc(ft_strlen(line) + 2);
		if (!temp)
			return (free(line), NULL);
		ft_strlcpy(temp, line, ft_strlen(line) + 1);
		temp[ft_strlen(line)] = c;
		temp[ft_strlen(line) + 1] = '\0';
		free(line);
		line = temp;
	}
	if (ret < 0 || (ret == 0 && *line == '\0'))
		return (free(line), NULL);
	return (line);
}

static t_list *read_heredoc_pipe(int fd)
{
	char	*line;
	t_list	*lines;

	lines = NULL;
	while(1)
	{
		line = read_line_pipe(fd);
		if (!line)
			break ;
		ft_lstadd_back(&lines, ft_lstnew(line));
	}
	return (lines);
}

static t_list	*handle_heredoc(char *delimiter)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
	t_list	*lines;

	if (pipe(pipe_fd) == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (close(pipe_fd[0]), close(pipe_fd[1]), NULL);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		child_process_heredoc(delimiter, pipe_fd[1]);
	}
	else
	{
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
		{
			lines = read_heredoc_pipe(pipe_fd[0]);
			close(pipe_fd[0]);
			return (lines);
		}
		//printf("wifsignaled(status) is: %d\nstatus is: %d\nwtermsig(status) is: %d\n and sigint is: %d\n",WIFSIGNALED(status), status, WTERMSIG(status), SIGINT);
		if (!WIFSIGNALED(status) && WTERMSIG(status) == 0)
		{
			write(STDOUT_FILENO, "> ^C\n", 5);
			close(pipe_fd[0]);
			errno = EINTR;
			return (NULL);
		}
		close(pipe_fd[0]);
	}
	return (NULL);
}

static char	**ft_setup_heredoc(char *input, t_heredoc **here)
{
	char	**splited;

	*here = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (!here)
		return (NULL);
	(*here)->helper = ft_replace(input);
	(*here)->line = NULL;
	splited = ft_split((*here)->helper, '<');
	if (splited && !splited[0])
	{
		clean_heredoc(*here);
		free(splited);
		return (NULL);
	}
	(*here)->num_brackets = ft_split_count(splited) - 1;
	return (splited);
}

t_list	*ft_heredoc(char *input)
{
	char		**splited;
	t_list		*lines;
	t_heredoc	*aux;
	int			i;
	void		(*old_sig[2])(int);

	lines = NULL;
	if (ft_strstr(input, "<<") == NULL)
		return (NULL);
	splited = ft_setup_heredoc(input, &aux);
	if (!splited)
		return (NULL);
	old_sig[0] = signal(SIGINT, SIG_IGN);
	old_sig[1] = signal(SIGQUIT, SIG_IGN);
	i = 1;
	errno = 0;
	while (i <= aux->num_brackets)
	{
		if (lines)
			ft_lstclear(&lines, free);
		lines = handle_heredoc(splited[i]);
		if (!lines && errno == EINTR)
			break ;
		i++;
	}
	signal(SIGINT, old_sig[0]);
	signal(SIGQUIT, old_sig[1]);
	clean_heredoc(aux);
	if (splited)
		free_split(splited, -1);
	return (lines);
}
