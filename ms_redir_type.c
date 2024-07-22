/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:55:13 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/19 09:55:18 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Function to check the type or redir. Returns 0 if there is no redir,
 * 1 if there is output redir, 2 if there is input redir and 3 if there is both
 * @param redirs A list of redirects. The t_list has a content which is a 
 * t_redir
 * @param type_aux The type of the redirect
 * @param type_redir The type of the redir
 */
static void	ms_type(t_list **redirs, int *type_aux, int *type_redir, char **nm)
{
	t_redir	*content;

	content = ((t_redir *)(*redirs)->content);
	if (redirs && *redirs)
		*type_aux = content->type;
	if (*type_aux == HERE_DOC)
	{
		*nm = content->k_word;
		content->k_word = ms_heredoc(content->k_word);
	}
	if (*type_aux == OUTFILE || *type_aux == OUTFILE_ADD)
	{
		if (*type_redir == 0)
			*type_redir = 1;
		else if (*type_redir == 2)
			*type_redir = 3;
	}
	else if ((*type_aux == INFILE) || (*type_aux == HERE_DOC))
	{
		if (*type_redir == 0)
			*type_redir = 2;
		else if (*type_redir == 1)
			*type_redir = 3;
	}
	*redirs = (*redirs)->next;
}

/**
 * @brief This function returns 0 if there is no redir, 1 if there is 
 * output redir, 2 if there is input redir and 3 if there is both.
 * @param command_list A list of commands a list of commands including
 * a list of arguments and a list of redirects. The t_list has a content which
 * is a t_command and the next. The t_command has a command which is the 
 * command, an argument list and a redirect list
*/
int	redir_type(t_list *command_list)
{
	t_list	*aux;
	t_list	*redirs;
	int		type_redir;
	int		type_aux;
	char	*name;

	name = NULL;
	aux = command_list;
	type_redir = 0;
	type_aux = -1;
	redirs = ((t_command *)(((t_list *)aux)->content))->redirs;
	while (redirs != NULL)
		ms_type(&redirs, &type_aux, &type_redir, &name);
	if (name)
		free (name);
	return (type_redir);
}
