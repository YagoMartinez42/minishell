/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:12:22 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/18 17:18:57 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
* @brief Auxiliary function to do the actual printing looping the argument list.
* @param *args It receives the list of arguments of echo.
*/
void	echo_print_args(t_list *args)
{
	while (args)
	{
		ft_printf("%s", args->content);
		args = args->next;
		if (args)
			ft_printf(" ");
	}
}

/**
* @brief Function to print the argument of "echo" in the stdout.
* @param *args It receives the list of arguments of echo.
*/
void	ft_echo(t_list *args)
{
	char	ender;
	int		aux;

	aux = 2;
	if (args)
	{
		if (ft_strncmp(args->content, "-n", 2) == 0)
		{
			while (((char *)(args->content))[aux] == 'n')
				aux++;
			if (((char *)(args->content))[aux] == '\0')
			{
				ender = '\0';
				args = args->next;
			}
			else
				return ;
		}
		else
			ender = '\n';
		echo_print_args(args);
		ft_printf("%c", ender);
	}
}
