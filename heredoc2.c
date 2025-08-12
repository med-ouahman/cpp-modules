/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:24:07 by aid-bray          #+#    #+#             */
/*   Updated: 2025/08/12 04:20:00 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
#include <sys/ioctl.h>

int heredoc_sig;

#define LENGTH 20

static int	create_heredoc_name(char *file_name)
{
	char	random_c[LENGTH + 1];
	int		i;
	int		fd;

	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
	{
		print_err1(strerror(errno));
		return (-1);
	}
	i = 0;
	while (i < LENGTH)
	{
		read(fd, random_c, LENGTH);
		if ('/' == random_c[i] || !ft_isprint(random_c[i]))
			continue ;
		file_name[i] = random_c[i];
		i++;
	}
	file_name[i] = '\0';
	close(fd);
	return (0);
}

static int	heredoc_exit(pid_t pid, int read_fd)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	handle_signals();
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 130)
		{
			printf("\n");
			helper_herdoc(NULL);
			close(read_fd);
			access_exit_code(130, WRITE);
			return (-1);
		}
	}
	return (0);
}

static int	create_heredoc_file(char *file_name, int *write_fd, int *read_fd)
{
	*write_fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (*write_fd < 0)
	{
		print_err2(file_name, strerror(errno));
		return (-1);
	}
	*read_fd = open(file_name, O_RDONLY);
	if (*read_fd < 0)
	{
		print_err1(strerror(errno));
		close(*write_fd);
		unlink(file_name);
		return (-1);
	}
	unlink(file_name);
	return (0);
}

int event_hook(void)
{
	return 0;
}

void	heredoc_handler(int so)
{
	(void)so;

	rl_done = 1;
	rl_end = 0;
	heredoc_sig = 1;
	rl_prompt = ft_strdup(get_prompt());
	access_exit_code(130, READ);
	signal(SIGINT, sigint_handler);
}

int	parser_heredoc(char *eof)
{
	int	writer;
	int	reader;
	char	filename[LENGTH + 1];
	char	*line;

	create_heredoc_name(filename);
	create_heredoc_file(filename, &writer, &reader);
	signal(SIGINT, heredoc_handler);
	rl_event_hook = event_hook;
	heredoc_sig = 0;
	while (!heredoc_sig)
	{
		line = readline(">");
		rl_done = 0;
		if (!line || 0 == ft_strcmp(line, eof))
			break ;
		write(writer, line, ft_strlen(line));
		free(line);
	}
	close(writer);
	return (reader);
}

int	parserr_he4444redoc(char *delim)
{
	char	file[LENGTH + 1];
	pid_t	pid;
	int		write_fd;
	int		read_fd;

	if (create_heredoc_name(file))
		return (-1);
	if (create_heredoc_file(file, &write_fd, &read_fd))
		return (-1);
	ignore_signals();
	pid = fork();
	if (pid < 0)
		return (print_err1(strerror(errno)), -1);
	if (!pid)
	{
		close(read_fd);
		read_heredoc(delim, write_fd);
	}
	close(write_fd);
	if (heredoc_exit(pid, read_fd))
		return (-1);
	return (read_fd);
}
