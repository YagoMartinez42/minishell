/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   exec_commands.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: dlanzas- <dlanzas-@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/07/08 10:10:16 by dlanzas-		  #+#	#+#			 */
/*   Updated: 2024/07/08 10:10:33 by dlanzas-		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Function to launch the command execution functions, when there is more
 * than one command
 * @param l_size The number of commands to execute
 * @param comm_list The list of commands to execute
 * @param data The data structure to handle the file descriptors and the pids
*/
static void	m_functions(t_execData *data, t_list *comm_list, int l_size)
{
	if (data->pid[data->count] == 0)
		m_start(comm_list->content, data->fd, data->r_type);
	if (l_size == 2)
		close(data->fd[data->count][1]);
	comm_list = comm_list->next;
	data->r_type = redir_type(comm_list);
	while (comm_list->next != NULL && l_size > 2)
	{
		close(data->fd[data->count % 2][1]);
		data->count++;
		m_launch(l_size, data->fd[data->count % 2], data->pid, data->count);
		if (data->pid[data->count] == 0)
			m_middle(comm_list->content, data->fd, data->count, data->r_type);
		comm_list = comm_list->next;
		if (comm_list != NULL)
			data->r_type = redir_type(comm_list);
		close(data->fd[(data->count + 1) % 2][0]);
	}
	data->count++;
	if (l_size > 2)
		close(data->fd[(data->count + 1) % 2][1]);
	m_launch_fork(data->pid, data->count);
	if (data->pid[data->count] == 0)
		m_end(comm_list->content, data->fd, data->count, data->r_type);
	close(data->fd[(data->count + 1) % 2][0]);
}

/**
 * @brief Function to select the execution of the commands
 * @param l_size The number of commands to execute
 * @param comm_list The list of commands to execute
 * @param data The data structure to handle the file descriptors and the pids
*/
static void	m_select(t_execData *data, t_list *comm_list, int l_size)
{
	if (l_size == 1)
		m_launch_fork(data->pid, data->count);
	else
		m_launch(l_size, data->fd[data->count], data->pid, data->count);
	signal(SIGQUIT, SIG_DFL);
	if (data->pid[data->count] == 0 && l_size == 1)
		execute_one(comm_list->content);
	else if (l_size > 1)
		m_functions(data, comm_list, l_size);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief Function to make forks and pipes for the execution of commands
 * Launches the command execution functions, when there is more than one command
 * @param l_size The number of commands to execute
 * @param command_list The list of commands to execute
*/
void	exec_commands(int l_size, t_list *command_list)
{
	int			status;
	int			aux;
	int			err;
	t_execData	data;

	data.count = 0;
	aux = -1;
	data.r_type = 0;
	data.r_type = redir_type(command_list);
	m_select(&data, command_list, l_size);
	signal(SIGINT, SIG_IGN);
	if (l_size == 1)
		waitpid(-1, &status, 0);
	else
	{
		while (++aux < l_size)
			waitpid(data.pid[aux], &status, 0);
	}
	if (WIFEXITED(status))
		err = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		err = (WTERMSIG(status) + 128);
	else
		err = 1;
	(signal(SIGINT, s_handler), ms_wideuse_values(&err, EXIT_CODE));
}
