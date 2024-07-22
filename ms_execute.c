/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:58:33 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/18 18:18:03 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Function to make pippe and fork
 * @param l_size The number of commands
 * @param fd[2] Array of two fd's
 * @param pid[1024] Array for the pid's
 * @param count The number of executed commands
*/
void	m_launch(int l_size, int fd[2], int pid[1024], int count)
{
	if (count < l_size - 1)
	{
		if (pipe(fd) != 0)
			(perror("pipe"), exit(errno));
	}
	pid[count] = fork();
	if (pid[count] < 0)
		(perror("fork"), exit(errno));
}

/**
 * Function to make fork
 * @param pid[1024] Array of ints for the pid
 * @param count The number of executed commands
*/
void	m_launch_fork(int pid[1024], int count)
{
	pid[count] = fork();
	if (pid[count] < 0)
		(perror("fork"), exit(errno));
}

/**
 * Function to start the execution
 * @param l_size The number of commands
 * @param command_list The struct with the commands, args and redirects
*/

void	execution(int l_size, t_list *command_list)
{
	if (!(command_list && (t_command *)command_list->content))
		return ;
	exec_commands(l_size, command_list);
}
