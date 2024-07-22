/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:56:36 by samartin          #+#    #+#             */
/*   Updated: 2023/10/11 15:39:31 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Adds a new command node to the command list
 * @param command_list The list of commands
 * @return The updated list of commands
*/
t_list	*add_command_set(t_list *command_list)
{
	t_list		*command_list_end;
	t_list		*new_node;
	t_command	*command;

	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		error_exit(101);
	new_node = ft_calloc(1, sizeof(t_list));
	if (!new_node)
		error_exit(101);
	new_node->content = command;
	if (!command_list)
		command_list = new_node;
	else
	{
		command_list_end = command_list;
		while (command_list_end->next)
			command_list_end = command_list_end->next;
		command_list_end->next = new_node;
	}
	return (command_list);
}

/**
 * @brief Returns the last command node in the command list
 * @param command_list The list of commands
*/
static t_command	*last_command(t_list *command_list)
{
	while (command_list->next)
		command_list = command_list->next;
	return ((t_command *)(command_list->content));
}

/**
 * @brief Adds a parameter to the last command node in the command list
 * @param command_list The list of commands
 * @param token The parameter to add
*/
void	add_param(t_list *command_list, char *token)
{
	t_command	*command_node;
	t_list		*iterator;
	t_list		*new_param;

	command_node = last_command(command_list);
	if (!command_node->command)
		command_node->command = token;
	else
	{
		new_param = ft_calloc(1, sizeof(t_list));
		if (!new_param)
			error_exit(101);
		new_param->content = token;
		if (!command_node->args)
			command_node->args = new_param;
		else
		{
			iterator = command_node->args;
			while (iterator->next)
				iterator = iterator->next;
			iterator->next = new_param;
		}
	}
}

/**
 * @brief Adds the type of the redirection to the last command node in the
 * command list
 * @param command_list The list of commands
 * @param token_type The type of the redirection
*/
void	add_redir_type(t_list *command_list, t_token_type token_type)
{
	t_command	*command_node;
	t_list		*iterator;
	t_list		*new_redir_node;
	t_redir		*redir;

	new_redir_node = ft_calloc(1, sizeof(t_list));
	if (!new_redir_node)
		error_exit(101);
	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		error_exit(101);
	redir->type = token_type;
	new_redir_node->content = redir;
	command_node = last_command(command_list);
	if (!command_node->redirs)
		command_node->redirs = new_redir_node;
	else
	{
		iterator = command_node->redirs;
		while (iterator->next)
			iterator = iterator->next;
		iterator->next = new_redir_node;
	}
}

/**
 * @brief Adds the keyword of the redirect to the last redirection node in the
 * command list
 * @param command_list The list of commands
 * @param token The keyword of the redirection
*/
void	add_redir_word(t_list *command_list, char *token)
{
	t_command	*command_node;
	t_list		*iterator;

	iterator = command_list;
	while (iterator->next)
		iterator = iterator->next;
	command_node = (t_command *)(iterator->content);
	iterator = command_node->redirs;
	while (iterator->next)
		iterator = iterator->next;
	((t_redir *)(iterator->content))->k_word = token;
}
