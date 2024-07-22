/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:24:46 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/04/19 19:01:24 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Is this erasable?
/**
 * @brief Command print function
 * @param command The command to print
*/
void	print_command(char **command)
{
	int	iter;

	iter = -1;
	while (command[++iter])
		printf("%s\n", command[iter]);
}

/**
 * @brief Counts the number of arguments in a list
 * @param args The list of arguments
*/
int	num_args(t_list *args)
{
	int		count;

	count = 0;
	while (args)
	{
		count++;
		args = args->next;
	}
	return (count);
}
