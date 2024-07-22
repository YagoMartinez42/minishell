/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_redirs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:51:51 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/18 20:37:32 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Complimentary function for b_type.
 * @param type_redir The type of the redir
 */
static void	set_redirs(int *type_redir, t_token_type type_aux)
{
	if (type_aux == OUTFILE || type_aux == OUTFILE_ADD)
	{
		if (*type_redir == 0)
			*type_redir = 1;
		else if (*type_redir == 2)
			*type_redir = 3;
	}
	else if ((type_aux == INFILE) || (type_aux == HERE_DOC))
	{
		if (*type_redir == 0)
			*type_redir = 2;
		else if (*type_redir == 1)
			*type_redir = 3;
	}
}

/**
 * @brief Function to check the type or redir. Returns 0 if there is no redir,
 * 1 if there is output redir, 2 if there is input redir and 3 if there is both
 * @param redirs A list of redirects. The t_list has a content which is a 
 * t_redir
 * @param type_redir The type of the redir
 * @param type_aux The type of the redirect
 */
static void	b_type(t_list **redirs, int *type_redir, int *type_aux)
{
	t_redir	*content;
	char	*name;

	name = NULL;
	content = ((t_redir *)(*redirs)->content);
	if (redirs && *redirs)
		*type_aux = content->type;
	if (*type_aux == HERE_DOC)
	{
		name = content->k_word;
		content->k_word = ms_heredoc(content->k_word);
	}
	set_redirs(type_redir, *type_aux);
	*redirs = (*redirs)->next;
	if (name)
		free (name);
}

/**
 * @brief Function must check redirs type:
 * 0 -> No redirs
 * 1 -> Outfile or outfileAdd
 * 2 -> infile
 * 3 -> Both
 * @param The builtin command
*/
static int	b_redirs_type(t_command	**com)
{
	t_command	*aux;
	t_list		*redirs;
	int			type_redir;
	int			type_aux;

	aux = *com;
	type_redir = 0;
	type_aux = -1;
	redirs = (t_list *)aux->redirs;
	while (redirs != NULL)
		b_type(&redirs, &type_redir, &type_aux);
	return (type_redir);
}

/**
 * @brief Function must check and change redirs if necessary
 * @param The builtin command
*/
void	b_redirs(t_command	**command)
{
	int	fdin_redir;
	int	fdout_redir;
	int	r_type;

	fdin_redir = 0;
	fdout_redir = 1;
	r_type = b_redirs_type(command);
	if (r_type == 1 || r_type == 3)
		fdout_redir = b_out_redir((*command)->redirs, \
			list_size((*command)->redirs));
	if (r_type == 2 || r_type == 3)
		fdin_redir = b_in_redir((*command)->redirs, \
			list_size((*command)->redirs));
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
