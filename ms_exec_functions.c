/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 19:10:57 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/18 13:38:11 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Function to execute the first command
 * @param command The command to execute
 * @param fd The file descriptor
 * @param r_type The type of redirection
*/
void	m_start(t_command *command, int fd[2][2], int r_type)
{
	int	fdin_redir;
	int	fdout_redir;

	fdin_redir = 0;
	fdout_redir = 1;
	if (r_type == 2 || r_type == 3)
		fdin_redir = execin_redir(command->redirs, list_size(command->redirs));
	if (r_type == 1 || r_type == 3)
		fdout_redir = execout_redir(command->redirs, \
			list_size(command->redirs));
	if (fdin_redir != 0)
		(dup2(fdin_redir, STDIN_FILENO), close(fdin_redir));
	if (fdout_redir != 1)
		(dup2(fdout_redir, STDOUT_FILENO), close(fdout_redir));
	else
		dup2(fd[0][1], STDOUT_FILENO);
	close(fd[0][0]);
	close(fd[0][1]);
	if (builtins(command, 0))
		(free_command(NULL, FREE), exit(EXIT_SUCCESS));
	else
		execute(command);
}

/**
 * @brief Function to execute the middle redirections
 * @param command The command to execute
 * @param r_type The type of redirection
 * @param f_in The file descriptor for input
 * @param f_out The file descriptor for output
*/
void	middle_redirs(t_command *command, int r_type, int *f_in, int *f_out)
{
	if (r_type == 2 || r_type == 3)
		*f_in = execin_redir(command->redirs, list_size(command->redirs));
	if (r_type == 1 || r_type == 3)
		*f_out = execout_redir(command->redirs, \
			list_size(command->redirs));
	if (!(command->command))
	{
		free_command(NULL, FREE);
		exit(0);
	}
}

/**
 * @brief Function to execute the middle commands
 * @param command The command to execute
 * @param fd The file descriptor
 * @param r_type The type of redirection
*/
void	m_middle(t_command *command, int fd[2][2], int count, int r_type)
{
	int	fdin_redir;
	int	fdout_redir;

	fdin_redir = 0;
	fdout_redir = 1;
	middle_redirs(command, r_type, &fdin_redir, &fdout_redir);
	close(fd[count % 2][0]);
	if (fdin_redir != 0)
		(dup2(fdin_redir, STDIN_FILENO), close(fdin_redir), \
		close(fd[(count + 1) % 2][0]));
	else
		(dup2(fd[(count + 1) % 2][0], STDIN_FILENO), \
		close(fd[(count + 1) % 2][0]));
	if (fdout_redir != 1)
		(dup2(fdout_redir, STDOUT_FILENO), close(fdout_redir), \
		close(fd[count % 2][1]));
	else
		(dup2(fd[count % 2][1], STDOUT_FILENO), close(fd[count % 2][1]));
	if (builtins(command, 0))
		(free_command(NULL, FREE), exit(EXIT_SUCCESS));
	else
		execute(command);
}

/**
 * @brief Function to execute the last command
 * @param command The command to execute
 * @param fd The file descriptor
 * @param r_type The type of redirection
*/
void	m_end(t_command *command, int fd[2][2], int count, int r_type)
{
	int		fdin_redir;
	int		fdout_redir;

	fdin_redir = 0;
	fdout_redir = 1;
	if (r_type == 2 || r_type == 3)
		fdin_redir = execin_redir(command->redirs, list_size(command->redirs));
	if (r_type == 1 || r_type == 3)
		fdout_redir = execout_redir(command->redirs, \
		list_size(command->redirs));
	if (fdin_redir != 0)
		(dup2(fdin_redir, STDIN_FILENO), close(fdin_redir), \
		close(fd[(count + 1) % 2][0]));
	else
		(dup2(fd[(count + 1) % 2][0], STDIN_FILENO), \
		close(fd[(count + 1) % 2][0]));
	if (fdout_redir != 1)
		(dup2(fdout_redir, STDOUT_FILENO), close(fdout_redir));
	if (builtins(command, 0))
		(free_command(NULL, FREE), exit(EXIT_SUCCESS));
	else
		execute(command);
}
