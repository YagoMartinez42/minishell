/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:34:02 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/22 16:12:41 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles fatal errors by displaying corresponding error messages and
 * exiting the shell completely.
 * @param num_error An integer that represents the error code passed to this
 * function. At proyect deliver time, there is only one code managed, when a
 * malloc has been unable to allocate memory.
 */
void	error_exit(int num_error)
{
	if (num_error == 101)
		perror("Error\nUnable to allocate memory.\n");
	else
		perror("Error\n(Untracked error).\n");
	exit (errno);
}

/**
 * @brief Handles different error cases and displays corresponding error
 * messages.
 * @param num_error An integer value that represents different error codes. The
 * function takes this error code as input and displays an appropriate error
 * message based on its value. The function also updates the `exit_code` in the
 * `values`structure accordingly. The two first are standard values used in
 * other shell programs, the rest are made ad-hoc for this minishell. 206
 * translates into exit code 1, but has a different message.
 */
void	error_prompt(int num_error)
{
	t_minishell	values;

	values = ms_wideuse_values(NULL, 0);
	values.exit_code = num_error;
	if (num_error == 1)
		write(2, "Error\nNo such file or directory.\n", 34);
	else if (num_error == 2)
		write(2, "Error\nSyntax error near unexpected token.\n", 43);
	else if (num_error == 201)
		write(2, "Error\nOpen quotes.\n", 20);
	else if (num_error == 202)
		write(2, "Error\nBroken pipe.\n", 20);
	else if (num_error == 203)
		write(2, "Error\nPermission denied.\n", 26);
	else if (num_error == 205)
		write(2, "Error\nUnable to get working directory. New wd is /.\n", 53);
	else if (num_error == 206)
	{
		write(2, "Error\nNot a valid identifier.\n", 31);
		values.exit_code = 1;
	}
	else
		perror("Error\n(Untracked error).\n");
	ms_wideuse_values(&values.exit_code, EXIT_CODE);
}

/**
 * @brief Iterates through a linked list and frees the memory allocated for
 * each node and its content.
 * @param list A pointer to the head of a linked list structure `t_list`. The
 * function iterates through the linked list, frees the memory allocated for
 * each node's content, then frees the memory allocated for the node itself.
 * Finally, it sets the freed node value to NULL.
 */
void	free_list(t_list *list)
{
	t_list	*tmp;

	while (list != NULL)
	{
		tmp = list;
		list = list->next;
		free(tmp->content);
		free(tmp);
		tmp = NULL;
	}
}
