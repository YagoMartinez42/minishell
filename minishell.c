/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 19:36:03 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/18 18:11:05 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Function to write the prompt
*/
static char	*compose_prompt(void)
{
	t_minishell	values;
	char		*prompt;
	char		*aux;

	values = ms_wideuse_values(NULL, 0);
	aux = ft_strjoin("🤖 minishell:", values.pwd);
	prompt = ft_strjoin(aux, ">> ");
	free(aux);
	return (prompt);
}

/**
 * @brief Function that checks if the line is empty
 * @param line The line to check
 * @param command_list The list of commands
 * @param l_size The size of the list
*/
static void	check_readline(char **line, t_list **command_list, int l_size)
{
	int	built;

	built = 0;
	if (!check_line(*line))
	{
		*command_list = tokenize_whole(*line);
		if (command_list)
		{
			free_command(*command_list, SET);
			l_size = list_size(*command_list);
			if (l_size == 1)
				built = builtins((t_command *)(*command_list)->content, l_size);
			if (built == 0)
				execution(l_size, *command_list);
			*command_list = clear_command_list(*command_list);
		}
	}
}

/**
 * @brief Function that waits for the commands that introduce the user to the
 * system
 * @param in The input file descriptor
 * @param out The output file descriptor
*/
void	listen(int in, int out)
{
	char		*line;
	char		*prompt;
	t_list		*command_list;
	int			l_size;

	l_size = 0;
	while (42)
	{
		(dup2(in, STDIN_FILENO), dup2(out, STDOUT_FILENO));
		set_ms_wd();
		prompt = compose_prompt();
		line = readline(prompt);
		if (!line)
			(free(line), exit(EXIT_SUCCESS));
		if (line[0] == '\0')
		{
			free(line);
			free(prompt);
			continue ;
		}
		add_history(line);
		remove_temps();
		check_readline(&line, &command_list, l_size);
		(free(prompt), free(line));
	}
}

int	main(int argc, char **argv, char **env)
{
	int	in;
	int	out;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	if (argc > 1)
	{
		argv[1] = NULL;
		return (127);
	}
	startup(env);
	listen(in, out);
	close(in);
	close(out);
	return (0);
}
