/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:31:16 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/19 19:46:34 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if the command is in the path
 * @param path The path to check
 * @param command The command to check
*/
char	*p_checkpath(char *path, char *command)
{
	char	**aux;
	char	*aux2;
	char	*result;
	int		c;

	if (!*command)
		return (NULL);
	c = -1;
	aux = ft_split(path, ':');
	(free(path), path = NULL);
	while (aux[++c])
	{
		aux2 = ft_strjoin("/", command);
		result = ft_strjoin(aux[c], aux2);
		(free(aux2));
		if (access(result, X_OK) == 0)
		{
			(ft_free(aux, c));
			return (result);
		}
		(free(result), result = NULL);
	}
	ft_free(aux, c);
	return (NULL);
}

/**
 * @brief Function to properly free if there's no comm
 * @param command The command to free
*/
static char	*close_ppath(char **command)
{
	char		*p_error;

	p_error = ft_strjoin("command error: ", *command);
	(perror(p_error), free(p_error), free(*command), exit (127));
	return (NULL);
}

/**
 * @brief Get the path of the command
 * @param command The command to get the path
*/
char	*p_path(char *command)
{
	int			i;
	int			j;
	char		*path;
	char		*comm;
	t_minishell	values;

	i = -1;
	j = -1;
	values = ms_wideuse_values(NULL, 0);
	while (values.env[++i])
	{
		if (ft_strncmp(values.env[i], "PATH=", 5) == 0)
		{
			path = malloc((ft_strlen(values.env[i]) - 4) * sizeof(char));
			if (!path)
				(free(path), path = NULL, perror("malloc"), exit(errno));
			while (values.env[i][++j + 5])
				path[j] = values.env[i][j + 5];
			path[j] = '\0';
			comm = p_checkpath(path, command);
			if (comm != NULL)
				return (comm);
		}
	}
	return (close_ppath(&command));
}
