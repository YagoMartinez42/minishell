/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:56:23 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/17 19:13:22 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Sets the current working directory inside the wideuse singleton
 * function.
 * If there is an error return from 'getcwd', shows an error and changes
 * directory to root.
 */
void	set_ms_wd(void)
{
	t_minishell	values;

	values = ms_wideuse_values(NULL, 0);
	if (getcwd(values.pwd, PATH_MAX) == NULL)
	{
		error_prompt(205);
		chdir("/");
		ms_wideuse_values("/", PWD);
	}
}

/**
 * @brief Changes the current directory and updates the environment variables
 * accordingly. OLDPWD changes only if the final working directory is different
 * than the previous.
 * @param path A string containing the path were we want to change to.
 */
void	ft_cd(char *path)
{
	char		*old_env_line;
	char		*env_line;
	char		*aux;
	t_minishell	values;

	values = ms_wideuse_values(NULL, 0);
	if (chdir(path) != 0)
		error_prompt(1);
	else
	{
		aux = ft_strdup(values.pwd);
		set_ms_wd();
		if (ft_strncmp(values.pwd, aux, ft_strlen(aux)))
		{
			old_env_line = ft_strjoin("OLDPWD=", aux);
			ft_export(old_env_line);
			free(old_env_line);
		}
		env_line = ft_strjoin("PWD=", values.pwd);
		ft_export(env_line);
		free(env_line);
		free(aux);
	}
}

/**
 *  @brief An enveloper to call ft_cd receiving here the full args list. If
 * there is somethin in next (more than 1 argument), it will be ignored.
 */
void	ft_cd_envel(t_list *args)
{
	if (args)
		ft_cd(args->content);
}
