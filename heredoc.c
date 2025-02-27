/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:09:18 by samartin          #+#    #+#             */
/*   Updated: 2024/07/19 17:22:11 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Continuously generates possible file names that would be already be
 * generated by a_good_name() and deletes all the correlative existing files
 * until it doesn't find the next possible name in the /tmp directory.
 */
void	remove_temps(void)
{
	char	*file_name;
	int		file_num;
	char	*num_str;
	int		done;

	done = 0;
	file_num = 0xFFFF;
	while (!done)
	{
		num_str = ft_itoa(file_num);
		if (!num_str)
			error_exit(101);
		file_name = ft_strjoin("/tmp/hd", num_str);
		free(num_str);
		if (!file_name)
			error_exit(101);
		if (!access(file_name, F_OK))
			unlink(file_name);
		else
			done = 1;
		free(file_name);
		file_num--;
	}
}

/**
 * @brief The function generates a unique file name by finding a hexadecimal
 * number,  * starting with FFFF and going decreading if there is any
 * (unprobably) existing coincidence, adding the hex result from itoab() to the
 * /tmp/hd base string and checking for the existence of the file in the /tmp.
 * The access() function returns -1 if the file doesn't exist.
 * @return The dynamically allocated (from ft_strjoin()) string with the file
 * name to use that is waranteed not to be already existing.
 */
static char	*a_good_name(void)
{
	char	*file_name;
	int		file_num;
	char	*num_str;

	file_num = 0xFFFF;
	while (42)
	{
		num_str = ft_itoab(file_num, 16);
		if (!num_str)
			error_exit(101);
		file_name = ft_strjoin("/tmp/hd", num_str);
		free(num_str);
		if (!file_name)
			error_exit(101);
		if (access(file_name, F_OK))
			break ;
		free(file_name);
		file_num--;
	}
	return (file_name);
}

/**
 * @brief Function to get the name of the temporal file and read the imput
 * @param keyword The word that stops the imput
 * @return The name of the temporal file
 */
static char	*get_heredoc(char *keyword)
{
	char	*line;
	char	*file_name;
	int		fd;
	int		key_len;

	key_len = ft_strlen(keyword);
	file_name = a_good_name();
	fd = open(file_name, O_CREAT | O_WRONLY, 0644);
	while (42)
	{
		line = readline("heredoc> ");
		if (!line || !ft_strncmp(line, keyword, key_len + 1))
		{
			(free(line), line = NULL);
			break ;
		}
		line = expand_vars(line);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
		line = NULL;
	}
	(free(line), close(fd), free(keyword));
	return (file_name);
}

/**
 * @brief The child process function that will manage the input of the heredoc
 * entry. It will get the file name from the get_heredoc() function and write it
 * to the pipe_fd[1] file descriptor. After that, it will close the pipe and
 * exit with success
 * @param pipe_fd The pipe file descriptors to write the file name to the parent
 * @param keyword The keyword used as the heredoc closer
*/
static void	im_child(int *pipe_fd, char *keyword)
{
	char	*file_name;

	close(pipe_fd[0]);
	signal(SIGINT, SIG_DFL);
	file_name = get_heredoc(keyword);
	ft_putstr_fd(file_name, pipe_fd[1]);
	close(pipe_fd[1]);
	free(file_name);
	exit(EXIT_SUCCESS);
}

/**
 * @brief Creates a temporary file to save a heredoc entry, using the keyword as
 * a limiter to end inputing. The process is forked and the child process will
 * manage the input while the parent remains waiting until it is finished.
 * @param keyword The keyword used as the heredoc closer. It will be passed to
 * the im_child() function and from there to the get_heredoc().
 * @return The file name obtained with get_next_line() from the child process.
 * If no name is gotten, newly malloced "/dev/null" string is returned.
 */
char	*ms_heredoc(char *keyword)
{
	int		pipe_fd[2];
	int		here_id;
	char	*file_name;

	pipe(pipe_fd);
	here_id = fork();
	if (here_id == 0)
		im_child(pipe_fd, keyword);
	signal(SIGINT, SIG_IGN);
	close(pipe_fd[1]);
	waitpid(here_id, NULL, 0);
	file_name = get_next_line(pipe_fd[0]);
	if (!file_name)
		file_name = ft_strdup("/dev/null");
	signal(SIGINT, s_handler);
	close(pipe_fd[0]);
	return (file_name);
}
