/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:54:56 by samartin          #+#    #+#             */
/*   Updated: 2024/04/06 18:46:08 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Counts the number of words in a string separated by a given character.
 * 
 * @param s The string that needs to be counted for words.
 * @param c The character that is used as a delimiter to separate words.
 *  
 * @return an integer value, which represents the number of words in the input
 * string s that are separated by the delimiter c.
 */
static int	count_words(const char *s, char c)
{
	unsigned int	i;
	unsigned int	wd_flg;
	unsigned int	count;

	i = 0;
	wd_flg = 0;
	count = 0;
	while (s[i] != 0)
	{
		if (s[i] == c)
		{
			if (wd_flg == 1)
				wd_flg = 0;
		}
		else
		{
			if (wd_flg == 0)
			{
				wd_flg = 1;
				count++;
			}
		}
		i++;
	}
	return (count);
}

/**
 * This function takes a string, a character, an array of strings, and an index,
 * and adds a word to the array of strings at the given index by allocating
 * memory and copying the characters from the string until the given character
 * is encountered.
 * 
 * @param s The pointer to a string that we want to extract a word from.
 * @param c The termination character that the function is searching for in the
 * string s. It stops adding characters to the word when it encounters this
 * character or the null terminator.
 * @param ws A pointer to a pointer of char, which represents an array of
 * strings. The function is designed to add a new word to this array.
 * @param i The index in the array of words (ws) where to add the current word.
 * 
 * @return a pointer to a character, which is the next character in the input
 * string after the word that was just added to the array of words.
 */
static const char	*add_word(const char *s, char c, char **ws, unsigned int i)
{
	unsigned int	len;
	unsigned int	j;

	len = 0;
	while (s[len] != c && s[len] != 0)
		len++;
	ws[i] = malloc (sizeof(char) * (len + 1));
	if (!ws[i])
	{
		while (i--)
			free(ws[i]);
		if (ws[i])
			free(ws[i]);
		return (NULL);
	}
	j = 0;
	while (j < len)
	{
		ws[i][j] = *s;
		s++;
		j++;
	}
	ws[i][j] = '\0';
	return (s);
}

/**
 * Splits a string into an array of substrings based on a given delimiter
 * character.
 * 
 * @param s The input string that needs to be split into words.
 * @param c A character that is used as a delimiter to split the input string
 * into multiple substrings. The function counts the number of substrings in
 * the input string and then allocates memory to store each substring in the
 * array.
 * 
 * @return A pointer to a pointer of characters (`char **`), meaning a
 * table or array of strings. The last element of the array is set to NULL.
 */
char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	unsigned int	str_count;
	char			**words;

	if (!s)
		return (NULL);
	str_count = count_words(s, c);
	words = malloc (sizeof(char *) * (str_count + 1));
	if (!words)
		return (NULL);
	i = 0;
	while (i < str_count)
	{
		while (*s == c)
			s++;
		s = add_word(s, c, words, i);
		if (!s)
		{
			free (words);
			return (NULL);
		}
		i++;
	}
	words[i] = NULL;
	return (words);
}
