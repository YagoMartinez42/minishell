/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:28:31 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/19 16:57:57 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Function to exit the minishell
 * @param args The list of arguments
*/
void	ft_exit(t_list *args)
{
	t_minishell	values;
	int			exit_code;

	values = ms_wideuse_values(NULL, 0);
	if (args && args->content)
	{
		exit_code = (long long)ft_atoi(args->content);
		if (!str_is_num(args->content))
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			exit(2);
		}
		else if (args->next)
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			values.exit_code = 1;
		}
		else
			(free_command(args, FREE), exit(exit_code));
	}
	else
		(free_command(args, FREE), exit(values.exit_code));
	ms_wideuse_values(&(values.exit_code), EXIT_CODE);
}
