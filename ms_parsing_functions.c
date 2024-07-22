/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:35:34 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/04/12 13:55:09 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Function to evaluate the state of the quotes in a given string.
 * @param c The character to evaluate.
 * @param quotes The current state of the quotes.
 * @return The new state of the quotes.
*/
t_q_status	eval_quotes_state(char c, t_q_status quotes)
{
	if (c == '\'' && quotes == NONE)
		return (SINGLE);
	if (c == '\'' && quotes == SINGLE)
		return (NONE);
	if (c == '\"' && quotes == NONE)
		return (DOUBLE);
	if (c == '\"' && quotes == DOUBLE)
		return (NONE);
	return (quotes);
}

/**
 * @brief Checks if a given string contains the character '$' and returns the
 * position  * of the first occurrence, or -1 if it is not found.
 * @param str A pointer to a string that we want to check for the presence of a
 * dollar sign.
 * @return The position of the first occurrence of the '$'or -1 if not found.
 */
int	check_dollar(char *str, int position)
{
	while (str[position] != '\0')
	{
		if (str[position] == '$')
			return (position);
		position++;
	}
	return (-1);
}

/**
 * @brief Checks if the redirect symbols make a valid redirection type and
 * returns which one, throwing and error 203 if the symbols make not a valid
 * redir. This function is also called from get_next_word() in tokenize.c.
 * @param line The string received with readline.
 */
t_token_type	check_redir_type(t_token_type t_type, char redir)
{
	if (t_type == NO_TOKEN)
	{
		if (redir == '<')
			return (INFILE);
		else if (redir == '>')
			return (OUTFILE);
	}
	else if (t_type == INFILE)
	{
		if (redir == '<')
			return (HERE_DOC);
		else if (redir == '>')
			return (WRONG_REDIR);
	}
	else if (t_type == OUTFILE)
	{
		if (redir == '>')
			return (OUTFILE_ADD);
		else if (redir == '<')
			return (WRONG_REDIR);
	}
	return (WRONG_REDIR);
}

/**
 * @brief Function to find the position of the first pipe character in a string.
 * @param str The string to search for the pipe character.
 * @return The position of the first pipe character in the string.
*/
int	find_pipe(char *str)
{
	int			count;
	t_q_status	quote;

	count = 0;
	quote = NONE;
	while (str[count])
	{
		quote = eval_quotes_state(str[count], quote);
		if (quote == NONE && str[count] == '|')
			return (count);
		count++;
	}
	return (count);
}

/**
 * @brief Function to count the size of the command list.
 * @param command_list The list of commands.
*/
int	list_size(t_list *command_list)
{
	int		size;
	t_list	*temp;

	size = 0;
	temp = command_list;
	while (temp != NULL)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}
