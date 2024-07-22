/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:36:34 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/19 19:38:28 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Takes a command structure, creates an array of arguments including the
 * command itself, terminates it with NULL and returns it.
 * @param command A 't_command' struct that contains the command. its arguments
 * and its redirects, which are ignored here.
 * @return A dynamically allocated array of strings with the command name at
 * it's first position, followed by its arguments and a NULL pointer at the end.
 */
char	**args_array(t_command command)
{
	int		size;
	int		cont;
	char	**commands;

	cont = 0;
	size = list_size(command.args);
	commands = ft_calloc(size + 2, sizeof(char **));
	if (command.command)
		commands[0] = ft_strdup(command.command);
	else
		commands[0] = ft_calloc(1, sizeof(char));
	while (command.args)
	{
		commands[++cont] = ft_strdup(command.args->content);
		command.args = command.args->next;
	}
	commands[++cont] = NULL;
	return (commands);
}

/**
 * @brief This function executes the command
 * @param command The structure that contains the command and its arguments
*/
void	execute(t_command *command)
{
	char		**commands;
	int			exe;
	t_minishell	values;

	if (!command || !(command->command))
		return ;
	commands = args_array(*command);
	values = ms_wideuse_values(NULL, 0);
	if (access(commands[0], X_OK))
		commands[0] = p_path(commands[0]);
	exe = execve(commands[0], commands, values.env);
	if (commands)
	{
		(ft_free(commands, list_size(command->args)), commands = NULL);
		(free(command), command = NULL);
	}
	if (exe < 0)
		(perror("execve"), exit(errno));
}

void	one_comm_redirs(t_command *command)
{
	int			fdin_redir;
	int			fdout_redir;

	fdin_redir = execin_redir(command->redirs, list_size(command->redirs));
	fdout_redir = execout_redir(command->redirs, list_size(command->redirs));
	if (fdin_redir != 0)
	{
		dup2(fdin_redir, STDIN_FILENO);
		close(fdin_redir);
	}
	if (fdout_redir != 1)
	{
		dup2(fdout_redir, STDOUT_FILENO);
		close(fdout_redir);
	}
}

/**
 * @brief This function executes the command when there`s only one command
 * @param command The structure that contains the command and its arguments
*/
void	execute_one(t_command *command)
{
	char		**commands;
	int			exe;
	t_minishell	values;
	int			args_size;

	exe = 0;
	args_size = list_size(command->args);
	if (command->redirs)
		one_comm_redirs(command);
	if (!(command->command))
		(free_command(NULL, FREE), exit(0));
	builtins(command, 0);
	commands = args_array(*command);
	values = ms_wideuse_values(NULL, 0);
	if (access(commands[0], X_OK) != 0)
		(commands[0] = p_path(commands[0]));
	free_command(command, FREE);
	if (commands)
		exe = execve(commands[0], commands, values.env);
	if (commands)
	{
		(ft_free(commands, args_size - 1), commands = NULL);
	}
	if (exe < 0)
		(perror("execve"), exit(errno));
}
