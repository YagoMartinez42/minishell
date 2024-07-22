/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:18:33 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/17 15:35:51 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
* @brief Function to print the working directory in stdout
* @param args The list of arguments, to be ignored as it should not take any.
*/
void	print_wd(t_list *args)
{
	t_minishell	values;

	(void)args;
	values = ms_wideuse_values(NULL, 0);
	printf("%s\n", values.pwd);
}
