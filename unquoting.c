/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquoting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:58:07 by samartin          #+#    #+#             */
/*   Updated: 2024/07/18 18:51:18 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Gets the next quote in a word
 * @param word The word to get the quote from
 * @return The index of the next quote in the word
*/
int	next_quote(char *word)
{
	int	i;

	i = 0;
	while (word[i] != '\'' && word[i] != '\"' && word[i] != '\0')
		i++;
	return (i);
}

/**
 * @brief Trims a segment of a word
 * @param segment The segment to be trimmed
 * @param quote The quote to be trimmed
*/
char	*trim_segment(char *segment, char *quote)
{
	char	*aux;

	if (!quote)
		return (segment);
	aux = segment;
	segment = ft_strtrim(segment, quote);
	if (aux)
		free(aux);
	return (segment);
}

/**
 * @brief Gets the next segment of a word
 * @param word The word to get the segment from
 * @param i The index of the word to start from
 * @param quotes The current quotes state
 * @return The next segment of the word
*/
char	*get_segment(char *word, int *i, t_q_status quotes)
{
	int		seg_len;
	char	*segment;
	char	*quote;

	if (quotes == NONE)
	{
		seg_len = next_quote(&(word[*i]));
		quote = NULL;
	}
	else
	{
		if (quotes == SINGLE)
			quote = "\'";
		else
			quote = "\"";
		seg_len = (int)(ft_strchr(&(word[(*i) + 1]), *quote) - &word[*i]) + 1;
	}
	segment = ft_substr(word, *i, seg_len);
	segment = trim_segment(segment, quote);
	*i += seg_len;
	return (segment);
}

/**
 * @brief Auxiliar function to check if the word and the segment
 * are correct and free aux and segment if needed
 * @param word_cpy A copy of the word
 * @param aux An auxiliar copy of the word
 * @param segment The segment of the word
*/
static void	check_xpd(char *word_cpy, char **aux, char **segment)
{
	if (*aux != word_cpy)
		free(*aux);
	if (*segment)
		free(*segment);
}

/**
 * @brief Unquotes and expands variables in a word
 * @param word The word to be unquoted and expanded
 * @return The unquoted and expanded word
*/
char	*unquote_n_xpd(char *word)
{
	t_q_status	quotes;
	char		*word_cpy;
	char		*segment;
	char		*aux;
	int			i;

	if (!word || !(ft_strchr(word, '\"') || ft_strchr(word, '\'')
			|| ft_strchr(word, '$')))
		return (word);
	word_cpy = ft_calloc(1, sizeof(char));
	i = 0;
	quotes = NONE;
	while (word[i])
	{
		quotes = eval_quotes_state(word[i], quotes);
		segment = get_segment(word, &i, quotes);
		if (quotes == NONE || quotes == DOUBLE)
			segment = expand_vars(segment);
		aux = word_cpy;
		word_cpy = ft_strjoin(word_cpy, segment);
		check_xpd(word_cpy, &aux, &segment);
		quotes = eval_quotes_state(word[i - 1], quotes);
	}
	free(word);
	return (word_cpy);
}
