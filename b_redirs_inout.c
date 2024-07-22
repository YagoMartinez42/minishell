/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_redirs_inout.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:38:55 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/18 18:12:16 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_exception(t_list *node)
{
	free(((t_redir *)(node->content))->k_word);
	free(node->content);
	free(node);
	error_prompt(203);
	listen(0, 1);
}

/**
 * @brief Returns fd when the redirect is of type INFILE or HERE-DOC
 * @param redir The list of redirects
 * @param l_size The size of the list
*/
int	b_in_redir(t_list *redir, int l_size)
{
	int		fd_redir;
	t_list	*aux;

	fd_redir = 0;
	aux = redir;
	while (l_size > 0)
	{
		if (((t_redir *)aux->content)->type == INFILE)
		{
			if (fd_redir > 0)
				close(fd_redir);
			if (((t_redir *)aux->content)->k_word != NULL)
				fd_redir = open(((t_redir *)aux->content)->k_word, O_RDONLY);
			if (fd_redir < 0)
				open_exception(redir);
		}
		if (aux->next)
			aux = aux->next;
		l_size--;
	}
	return (fd_redir);
}

/**
 * @brief Auxiliar function to open the files
 * @param fd_redir The file descriptor
 * @param aux The list of redirects
*/
static void	f_redir(int *fd_redir, t_list *aux)
{
	if (((t_redir *)aux->content)->type == OUTFILE)
	{
		if (*fd_redir > 1)
			close(*fd_redir);
		if (ft_strlen(((t_redir *)aux->content)->k_word) > 0)
			*fd_redir = open(((t_redir *)aux->content)->k_word, O_WRONLY \
		| O_CREAT | O_TRUNC, 0644);
		else
			open_exception(aux);
		if (*fd_redir < 0)
			open_exception(aux);
	}
	else if (((t_redir *)aux->content)->type == OUTFILE_ADD)
	{
		if (*fd_redir > 1)
			close(*fd_redir);
		if (ft_strlen(((t_redir *)aux->content)->k_word) > 0)
			*fd_redir = open(((t_redir *)aux->content)->k_word, O_WRONLY \
		| O_APPEND | O_CREAT, 0644);
		if (*fd_redir < 0)
			open_exception(aux);
	}
}

/**
 * @brief Returns fd when the redirect is of type OUTFILE or OUTFILE_ADD
 * @param redir The list of redirects
 * @param l_size The size of the list
*/
int	b_out_redir(t_list *redir, int l_size)
{
	int		fd_redir;
	t_list	*aux;

	fd_redir = 1;
	aux = redir;
	while (l_size > 0)
	{
		f_redir(&fd_redir, aux);
		l_size--;
		if (aux->next)
			aux = aux->next;
	}
	return (fd_redir);
}
