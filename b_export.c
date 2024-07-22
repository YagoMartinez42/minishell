/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:53:03 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/18 15:47:57 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Adds a new environment variable to the existing environment pulled
 * from the singleton function 'ms_wideuse_values'.
 * @param args A string representing the new environment variable in the format
 * "KEY=VALUE".
 */
static void	add_to_env(char *args)
{
	int			line;
	char		**aux_env;
	t_minishell	values;

	values = ms_wideuse_values(NULL, 0);
	line = -1;
	aux_env = ft_calloc((env_len(values.env) + 2), sizeof(char *));
	while (++line < env_len(values.env))
	{
		aux_env[line] = ft_strdup(values.env[line]);
		free(values.env[line]);
	}
	aux_env[line] = ft_strdup(args);
	free (values.env);
	ms_wideuse_values (aux_env, ENV);
}

/**
 * @brief Replaces a specific environment variable with a new value in the array
 * of  * environment variables pulled from the singleton 'ms_wideuse_values'.
 * @param args A string that represents the new value that you want to replace
 * in the environment variable containing the full new line .
 * @param name A string containing only the name part of an environment
 * variable. This function is designed to replace the full line of the specified
 * environment variable with the provided 'args' line.
 */
static void	replace_in_env(char *args, char *name)
{
	t_minishell	values;
	char		*aux_env_line;
	int			iter;

	iter = -1;
	values = ms_wideuse_values (NULL, 0);
	while (values.env[++iter] && ft_strncmp(values.env[iter], name, \
			ft_strlen(name)))
		continue ;
	if (!ft_strncmp(values.env[iter], name, ft_strlen(name)))
	{
		aux_env_line = ft_strdup(args);
		free(values.env[iter]);
		values.env[iter] = aux_env_line;
	}
}

/**
 * @brief Checks the type of the key given compared with what is already in the
 * environment.
 * @param arg A string with the argument being checked for export type.
 * @param name A pointer to string passed this way to preserve it after scope
 * without being part of the return. This parameter is used to store the name
 * extracted from the input argument 'arg' if it meets the conditions not to be
 * INVALID.
 * @return A value of type 't_exports' (from enum) which indicates the type of
 * the export based on the input argument. The possible return values are NEW,
 * EXISTS or INVALID.
 */
static t_exports	check_export_type(char *arg, char **name)
{
	t_exports	type;
	t_minishell	values;
	int			iter;

	iter = -1;
	type = INVALID;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (type);
	values = ms_wideuse_values(NULL, 0);
	while (ft_isalnum(arg[++iter]) || arg[iter] == '_')
		continue ;
	if (arg[iter] == '=')
	{
		type = NEW;
		*name = ft_calloc((iter + 1), sizeof(char));
		ft_strlcpy(*name, arg, iter + 1);
	}
	iter = -1;
	while (type == NEW && values.env[++iter])
	{
		if (!ft_strncmp(values.env[iter], *name, ft_strlen(*name)) \
			&& values.env[iter][ft_strlen(*name)] == '=')
			type = EXISTS;
	}
	return (type);
}

/**
 * @brief Checks the type of an export argument (INVALID, NEW or EXISTS),
 * updates the  * environment variable if it exists, and adds it to the
 * environment if it doesn't.
 * @param args The argument passed to the export command. This argument
 * should be a variable assignment in the format "key=value".
 */
void	ft_export(char *arg)
{
	t_exports	type;
	char		*name;

	name = NULL;
	type = check_export_type(arg, &name);
	if (type == NEW)
		add_to_env(arg);
	else if (type == EXISTS)
		replace_in_env(arg, name);
	else
		error_prompt(206);
	if (name)
		free (name);
}

/**
 *  @brief An enveloper to call ft_export receiving here the full args list.
 * If there is somethin in next (more than 1 argument), it will be ignored.
 */
void	ft_exp_envel(t_list *args)
{
	if (!args)
		print_env(args);
	while (args)
	{
		ft_export(args->content);
		args = args->next;
	}
}
