/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:20:34 by samartin          #+#    #+#             */
/*   Updated: 2024/01/25 15:45:36 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Function to handle the signals.
 * @param sig The signal to handle.
*/
void	s_handler(int sig)
{
	int	exitc;

	exitc = 1;
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ms_wideuse_values(&exitc, EXIT_CODE);
	}
}
