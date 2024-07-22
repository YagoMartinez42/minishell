/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:54:15 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/18 20:34:49 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
* @brief Checks if there are unpaired quote symbols that are supposed to
* envelope * sentences instead of being used as literal part of a sentence.
* Throws an error 201 if at the end of the line there is a quote status still
* not closed by its pair.
* @param line A string containing a line of text.
*/
static int	check_open_quotes(char *line)
{
	t_q_status	q_status;

	q_status = NONE;
	while (*line)
	{
		q_status = eval_quotes_state(*line, q_status);
		line++;
	}
	if (q_status != NONE)
	{
		error_prompt(201);
		return (201);
	}
	return (0);
}

/**
 * @brief This sub-function for 'check_pipe_error()' checks if after a pipe
 * symbol  * there is nothing before another pipe or the end of the line.
 * @param line The "line" is passed as a double pointer to preserve its
 * position after returning.
 * @return Zero if there is no error, 202 if there is.
 */
static int	check_empty_pipe(char **line)
{
	(*line)++;
	while (is_whitespace(**line))
		(*line)++;
	if (**line == '|' || **line == '\0')
	{
		error_prompt(202);
		return (202);
	}
	return (0);
}

/**
* @brief Checks if there are pipe symbols that are not preceded and followed by
* other words. If there is a broken pipe an error 202 occurs.
* @param line The string received with readline.
**/
static int	check_pipe_error(char *line)
{
	t_q_status	quotes;

	while (is_whitespace(*line))
		line++;
	if (*line == '|')
	{
		error_prompt(202);
		return (202);
	}
	quotes = NONE;
	while (*line)
	{
		quotes = eval_quotes_state(*line, quotes);
		while (is_whitespace(*line))
			line++;
		if (quotes == NONE && *line == '|')
		{
			if (check_empty_pipe(&line))
				return (202);
		}
		if (*line)
			line++;
	}
	return (0);
}

/**
 * @brief Checks if there are redirect symbols outside quotations that are not
 * followed by another word. Uses the check_redir_type sub-function to throw an
 * error in case.
 * @param line The string received with readline.
 */
static int	check_redir_error(char *line)
{
	t_q_status		quotes;
	t_token_type	t_type;

	quotes = NONE;
	t_type = NO_TOKEN;
	while (*line && t_type != WRONG_REDIR)
	{
		quotes = eval_quotes_state(*line, quotes);
		if (quotes == NONE)
		{
			if (*line == '<' || *line == '>')
				t_type = check_redir_type(t_type, *line);
			else
				t_type = NO_TOKEN;
		}
		else
			t_type = NO_TOKEN;
		line++;
	}
	if (t_type == WRONG_REDIR)
	{
		error_prompt(2);
		return (2);
	}
	return (0);
}

/**
* @brief Checks some basic syntax errors before trying to parse the line. If
* there are unclosed quotation, if there are wrong pipes, or if there are wrong
* redir symbols, the line will not be considered for execution.
* @param line The string containing a line of text received from the readline().
*/
int	check_line(char *line)
{
	int	errnum;

	errnum = 0;
	if (skip_whitespace(line) == ft_strlen(line))
		errnum = 200;
	if (!errnum)
		errnum = check_open_quotes(line);
	if (!errnum)
		errnum = check_pipe_error(line);
	if (!errnum)
		errnum = check_redir_error(line);
	return (errnum);
}
