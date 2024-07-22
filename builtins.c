/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:17:51 by samartin          #+#    #+#             */
/*   Updated: 2024/07/19 19:24:55 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Allocates memory for an array of fuction pointers and fills it with
 * each function.
 * @return The full array of fuctions.
 */
static t_p2built	*populate_functions(void)
{
	t_p2built	*bi_funct;

	bi_funct = malloc(7 * sizeof (t_p2built));
	if (!bi_funct)
		error_exit(101);
	bi_funct[0] = print_wd;
	bi_funct[1] = ft_cd_envel;
	bi_funct[2] = ft_echo;
	bi_funct[3] = ft_exp_envel;
	bi_funct[4] = print_env;
	bi_funct[5] = ft_unset;
	bi_funct[6] = ft_exit;
	return (bi_funct);
}

/**
 * @brief Allocates memory for an array of strings representing built-in
 * commands and  fills it with each word.
 * @return The full array of command words.
 */
static char	**populate_command_words(void)
{
	char	**bi_com;

	bi_com = malloc(7 * sizeof (char *));
	if (!bi_com)
		error_exit(101);
	bi_com[0] = ft_strdup("pwd");
	bi_com[1] = ft_strdup("cd");
	bi_com[2] = ft_strdup("echo");
	bi_com[3] = ft_strdup("export");
	bi_com[4] = ft_strdup("env");
	bi_com[5] = ft_strdup("unset");
	bi_com[6] = ft_strdup("exit");
	return (bi_com);
}

/**
 * @brief Frees memory of the arrays previously used in the functions of this
 * file.
 * @param bi_funt The array of function pointers.
 * @param bi_com The array of command words. Each malloced string is also to be
 * freed.
 */
static void	clean_arrays(t_p2built *bi_funct, char **bi_com)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		free(bi_com[i]);
		i++;
	}
	free(bi_com);
	free(bi_funct);
}

/**
 * @brief Checks if a command matches any built-in commands and executes the
 * corresponding function, otherwise it proceeds with the execution of the
 * command.
 * 
 * @param command_node A pointer to a node in a linked list that contains
 * the struct of command, arguments and redirects information.
 * @param l_size The full size of the command list.
 */
int	builtins(t_command *com, int l_size)
{
	t_p2built	*bi_funct;
	char		**bi_com;
	int			i;

	if (!com || !(com->command))
		return (0);
	bi_funct = populate_functions();
	bi_com = populate_command_words();
	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(com->command, bi_com[i], ft_strlen(bi_com[i]) + 1))
		{
			if (l_size == 1 && com->redirs)
				(b_redirs(&com));
			bi_funct[i](com->args);
			clean_arrays(bi_funct, bi_com);
			return (1);
		}
		i++;
	}
	clean_arrays(bi_funct, bi_com);
	return (0);
}
