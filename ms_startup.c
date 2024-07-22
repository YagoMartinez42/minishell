/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_startup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:56:24 by samartin          #+#    #+#             */
/*   Updated: 2024/07/15 13:35:35 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Increments the value of the SHLVL environment variable by 1.
 * 
 * @param shlvl A string that contains the current value of the SHLVL
 * environment variable. It is expected to be in the format "SHLVL=<number>",
 * so the string is displaced 6 bytes to send the number to ft_atoi, being it
 * the current level value that needs to be incremented by 1 and converted back
 * into string.
 * 
 * @return A new string in the format "SHLVL=<new_level>".
 */
static char	*ms_add_lvl(char *shlvl)
{
	int		lvl;
	char	*lvlstr;
	char	*new_shlvl;

	lvl = ft_atoi(shlvl + 6) + 1;
	lvlstr = ft_itoa(lvl);
	if (!lvlstr)
		error_exit(101);
	new_shlvl = ft_strjoin("SHLVL=", lvlstr);
	if (!new_shlvl)
		error_exit(101);
	free(lvlstr);
	return (new_shlvl);
}

/**
 * @brief Sets the environment variable "SHELL" to "/bin/minishell".
 * 
 * @return A string containing the value "SHELL=/bin/minishell".
 */
static char	*ms_set_mini(void)
{
	char	*ms_path_line;

	ms_path_line = ft_strdup("SHELL=/bin/minishell");
	if (!ms_path_line)
		error_exit(101);
	return (ms_path_line);
}

/**
 * @brief Reconstructs the environment variables if the env is NULL
 * @param pwd The current working directory
 * @return A char ** with the new environment variable
*/
static char	**ms_reconstruct_env(char *pwd)
{
	char	**env;
	char	*path_line;
	char	*pwd_line;

	env = (char **)ft_calloc(5, sizeof(char *));
	if (!env)
		error_exit(101);
	env[0] = ms_set_mini();
	env[1] = ms_add_lvl("SHLVL=0");
	path_line = ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	if (!path_line)
		error_exit(101);
	env[2] = path_line;
	pwd_line = ft_strjoin("PWD=", pwd);
	if (!pwd_line)
		error_exit(101);
	env[3] = pwd_line;
	return (env);
}

/**
 * @brief Copies the environment variables to a new char **.
 * @param env The environment variables to copy.
 * @return A char ** with the new environment variables.
*/
static char	**ms_copy_env(char **env)
{
	char	**env_c;
	int		i;

	env_c = (char **)ft_calloc(env_len(env) + 1, sizeof(char *));
	if (!env_c)
		error_exit(101);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "SHLVL=", 6))
			env_c[i] = ms_add_lvl(env[i]);
		else if (!ft_strncmp(env[i], "SHELL=", 6))
			env_c[i] = ms_set_mini();
		else
		{
			env_c[i] = (char *)ft_calloc((ft_strlen(env[i]) + 1), sizeof(char));
			if (!env_c[i])
				error_exit(101);
			ft_strlcpy(env_c[i], env[i], ft_strlen(env[i]) + 1);
		}
	}
	env_c[i] = NULL;
	return (env_c);
}

/**
 * @brief Initializes the minishell with the environment variables.
 * @param env The environment variables.
*/
void	startup(char **env)
{
	char	**env_c;
	char	*pwd;

	pwd = (char *)ft_calloc(PATH_MAX, sizeof(char));
	if (!pwd)
		error_exit(101);
	getcwd(pwd, PATH_MAX);
	if (!env || env[0] == NULL)
		env_c = ms_reconstruct_env(pwd);
	else
		env_c = ms_copy_env(env);
	ms_wideuse_values(env_c, ENV);
	ms_wideuse_values(pwd, PWD);
	signal(SIGINT, s_handler);
	signal(SIGQUIT, SIG_IGN);
}
