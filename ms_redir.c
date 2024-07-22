/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:41:54 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/18 16:02:28 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Aux function to check if the redirect is of type INFILE or HERE_DOC
 * @param aux The list of redirects
 * @param fd_redir The file descriptor
*/
static void	check_infile(t_list **aux, int *fd_redir)
{
	t_redir	*content;

	content = ((t_redir *)(*aux)->content);
	if (((t_redir *)content)->type == INFILE
		|| ((t_redir *)content)->type == HERE_DOC)
	{
		if (*fd_redir > 0)
			close(*fd_redir);
		if (ft_strlen(((t_redir *)content)->k_word) > 0)
		{
			*fd_redir = open(((t_redir *)content)->k_word, O_RDONLY);
		}
		else
			(free_command(NULL, FREE), ft_printf("syntax error\n"), \
			exit(2));
		if (*fd_redir < 0)
			(free_command(NULL, FREE), perror("open"), exit(2));
	}
}

/**
 * @brief Returns fd when the redirect is of type INFILE or HERE-DOC
 * @param redir The list of redirects
 * @param l_size The size of the list
*/
int	execin_redir(t_list *redir, int l_size)
{
	int		fd_redir;
	t_list	*aux;

	fd_redir = 0;
	aux = redir;
	while (l_size > 0)
	{
		check_infile(&aux, &fd_redir);
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
static void	file_redir(int *fd_redir, t_list **aux)
{
	if (((t_redir *)(*aux)->content)->type == OUTFILE)
	{
		if (*fd_redir > 1)
			close(*fd_redir);
		if (ft_strlen(((t_redir *)(*aux)->content)->k_word) > 0)
			*fd_redir = open(((t_redir *)(*aux)->content)->k_word, O_WRONLY \
		| O_CREAT | O_TRUNC, 0644);
		else
			(free_command(NULL, FREE), ft_printf("syntax error\n"), exit(2));
		if (*fd_redir < 0)
			(free_command(NULL, FREE), perror("open"), exit(errno));
	}
	else if (((t_redir *)(*aux)->content)->type == OUTFILE_ADD)
	{
		if (*fd_redir > 1)
			close(*fd_redir);
		if (ft_strlen(((t_redir *)(*aux)->content)->k_word) > 0)
			*fd_redir = open(((t_redir *)(*aux)->content)->k_word, O_WRONLY \
		| O_APPEND | O_CREAT, 0644);
		if (*fd_redir < 0)
			(free_command(NULL, FREE), perror("open"), exit(errno));
	}
}

/**
 * @brief Returns fd when the redirect is of type OUTFILE or OUTFILE_ADD
 * @param redir The list of redirects
 * @param l_size The size of the list
*/
int	execout_redir(t_list *redir, int l_size)
{
	int		fd_redir;
	t_list	*aux;

	fd_redir = 1;
	aux = redir;
	while (l_size > 0)
	{
		file_redir(&fd_redir, &aux);
		if (aux->next)
			aux = aux->next;
		l_size--;
	}
	return (fd_redir);
}
