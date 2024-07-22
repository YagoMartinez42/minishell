/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_wideuse_values.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:20:16 by samartin          #+#    #+#             */
/*   Updated: 2024/04/18 16:08:23 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Function to get the length of the environment variables.
 * @param env The environment variables.
*/
int	env_len(char **env)
{
	int	count;

	count = 0;
	if (env)
	{
		while (env[count])
			count++;
	}
	return (count);
}

/**
 * @brief Function to set & get the environment variables.
 * @param setting The setting to set.
 * @param wvar The type of variable to set.
*/
t_minishell	ms_wideuse_values(void *setting, int wvar)
{
	static t_minishell	bender_shell;

	if (setting)
	{
		if (wvar == ENV)
			bender_shell.env = (char **)setting;
		else if (wvar == PWD)
			bender_shell.pwd = (char *)setting;
		else if (wvar == EXIT_CODE)
			bender_shell.exit_code = *(int *)setting;
	}
	return (bender_shell);
}

/**
 * @brief Function to get the exit code as a string.
 * @return char* The exit code as a string.
*/
char	*get_str_exit_code(void)
{
	t_minishell	values;

	values = ms_wideuse_values(NULL, 0);
	return (ft_itoa(values.exit_code));
}

/**
 * @brief Function to print the environment variables.
*/
void	print_env(t_list *args)
{
	int			line;
	int			len;
	t_minishell	values;

	(void)args;
	values = ms_wideuse_values(NULL, 0);
	line = -1;
	len = env_len(values.env);
	while (++line < len)
		printf("%s\n", values.env[line]);
}
