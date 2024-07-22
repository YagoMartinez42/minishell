/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:19:54 by samartin          #+#    #+#             */
/*   Updated: 2024/07/19 18:55:49 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees the memory allocated for the arguments of a command.
 * @param arg_node The node of the list of arguments to be freed.
*/
static void	clear_args_list(t_list *arg_node)
{
	t_list	*aux;

	while (arg_node)
	{
		free(arg_node->content);
		aux = arg_node;
		arg_node = arg_node->next;
		free(aux);
	}
}

/**
 * @brief Frees the memory allocated for the redirections of a command.
 * @param redir_node The node of the list of redirections to be freed.
*/
static void	clear_red_list(t_list *redir_node)
{
	t_list	*aux;

	while (redir_node)
	{
		if (redir_node->content)
		{
			free(((t_redir *)(redir_node->content))->k_word);
			free(redir_node->content);
			redir_node->content = NULL;
		}
		aux = redir_node;
		redir_node = redir_node->next;
		free(aux);
	}
}

/**
 * @brief Frees the memory allocated for the command list.
 * @param command_list The list of commands to be freed.
*/
t_list	*clear_command_list(t_list *command_list)
{
	t_list	*command_node;
	t_list	*aux;

	command_node = command_list;
	while (command_node)
	{
		if ((t_command *)(command_node->content))
		{
			if (((t_command *)(command_node->content))->args)
				clear_args_list(((t_command *)(command_node->content))->args);
			if (((t_command *)(command_node->content))->redirs)
				clear_red_list(((t_command *)(command_node->content))->redirs);
			free(((t_command *)(command_node->content))->command);
			if (command_node->content)
				free(command_node->content);
			command_node->content = NULL;
		}
		aux = command_node;
		command_node = command_node->next;
		free(aux);
	}
	command_list = NULL;
	return (command_list);
}

void	free_command(void *command, t_free type)
{
	static t_list	*aux;

	if (type == SET)
		aux = (t_list *)command;
	else if (type == FREE && aux != NULL)
		clear_command_list(aux);
}
