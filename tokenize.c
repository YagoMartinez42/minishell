/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:10:31 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/19 19:11:10 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Looks for redirects in the command line
 * @param c_segment The command set to be tokenized
 * @param token_type The type of token to be added to the linked list
 * @param pos The position of the next token in the command set
 * @param q_status The status of the quotes
*/
static int	gnw_aux(char **c_segment, t_token_type *token_type, int *pos, \
	t_q_status q_status)
{
	int	i;

	i = 0;
	while (**c_segment == '<' || **c_segment == '>')
	{
		*token_type = check_redir_type(*token_type, **c_segment);
		(*c_segment)++;
		(*pos)++;
	}
	if (*token_type == WRONG_REDIR)
		return (-1);
	if (*token_type > ARG)
		return (0);
	*token_type = ARG;
	while ((*c_segment)[i] && (q_status != NONE
				|| !(is_whitespace((*c_segment)[i])
				|| (*c_segment)[i] == '<' || (*c_segment)[i] == '>'
				|| (*c_segment)[i] == '|')))
	{
		i++;
		(*pos)++;
		q_status = eval_quotes_state((*c_segment)[i], q_status);
	}
	return (i);
}

/**
 * @brief Finds the position of the next pipe character in the command set
 * and adds the next command
 * @param c_segment The command set to be tokenized.
 * @param token_type The type of token to be added to the linked list.
 * @param pos The position of the next token in the command set.
 * @return A pointer to the next word in the command set.
*/
static char	*get_next_word(char *c_segment, t_token_type *token_type, int *pos)
{
	char		*word;
	t_q_status	q_status;
	int			i;

	word = NULL;
	q_status = eval_quotes_state(*c_segment, NONE);
	i = gnw_aux(&c_segment, token_type, pos, q_status);
	if (i < 0)
		return (NULL);
	if (*token_type == ARG)
	{
		word = malloc((i + 1) * sizeof(char));
		if (!word)
			error_exit(101);
		word[i] = '\0';
	}
	while (i)
	{
		i--;
		word[i] = c_segment[i];
	}
	word = unquote_n_xpd(word);
	return (word);
}

/**
 * @brief Finds the position of the next pipe character in the command set
 * and adds the next command
 * @param c_set The command set to be tokenized.
 * @param c_list The linked list of commands to be filled with the tokens.
 * @param t_data The token data to be added to the linked list.
*/
static char	*t_list_type(t_token *t_data, t_list **c_list, char *c_set)
{
	if (t_data->token_type == ARG)
		add_param(*c_list, t_data->token);
	else
	{
		add_redir_type(*c_list, t_data->token_type);
		t_data->token_type = NO_TOKEN;
		t_data->token = get_next_word(c_set + t_data->pos, \
			&t_data->token_type, &t_data->pos);
		if (t_data->token_type != ARG)
		{
			error_prompt(2);
			clear_command_list(*c_list);
			if (t_data->token)
				free(t_data->token);
			return (NULL);
		}
		add_redir_word(*c_list, t_data->token);
		t_data->pos += skip_whitespace(c_set + (t_data->pos));
	}
	return (c_set);
}

/**
 * @brief Auxiliar function to init the tokenize
 * @param c_list The linked list of commands to be filled with the tokens.
 * @param c_set The command set to be tokenized.
 * @param c_size The size of the command set.
 * @return A pointer to the linked list of commands.
 */
static t_list	*tokenize_command_set(char *c_set, t_list *c_list, int c_size)
{
	t_token			t_data;

	t_data.pos = 0;
	t_data.token_type = NO_TOKEN;
	c_list = add_command_set(c_list);
	while (t_data.pos < c_size)
	{
		t_data.pos += skip_whitespace(c_set + t_data.pos);
		t_data.token = get_next_word(c_set + t_data.pos, &t_data.token_type, \
			&t_data.pos);
		if (!t_data.token && t_data.token_type == ARG)
		{
			error_prompt(2);
			clear_command_list(c_list);
			if (t_data.token)
				free(t_data.token);
			return (NULL);
		}
		t_data.pos += skip_whitespace(c_set + t_data.pos);
		if (!t_list_type(&t_data, &c_list, c_set))
			return (NULL);
		t_data.token_type = NO_TOKEN;
	}
	return (c_list);
}

/**
 * @brief Tokenizes (turns everything into sorted and understandable set of
 * commands, arguments and redirects) a whole command line separated by pipes
 * and returns a linked list of commands.
 * @param line The whole command line as inputed the function iterates through
 * it, finding the position of the next pipe character if there is any left.
 * @return A pointer to a linked list of tokens, t_list * type).
 */
t_list	*tokenize_whole(char *line)
{
	int		cs_end;
	t_list	*command_list;

	command_list = NULL;
	while (*line != '\0')
	{
		cs_end = find_pipe(line);
		command_list = tokenize_command_set(line, command_list, cs_end);
		if (!command_list)
			return (NULL);
		if (line[cs_end] == '|')
			line += cs_end + 1;
		else
			break ;
	}
	return (command_list);
}
