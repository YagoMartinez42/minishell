/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lib_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:30:17 by dlanzas-          #+#    #+#             */
/*   Updated: 2023/12/20 16:14:35 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Function to free the substr for the libft functions
 * @param substr The substr to free
 * @param num The number of substrs to free
*/
void	*ft_free(char **substr, int num)
{
	while (num >= 0)
	{
		free(substr[num]);
		substr[num] = NULL;
		num--;
	}
	free(substr);
	substr = NULL;
	return (NULL);
}

/**
 * @brief Function to free the values struct
*/
void	ft_free_all(void)
{
	int			i;
	t_minishell	values;

	values = ms_wideuse_values(NULL, 0);
	i = 0;
	while (values.env[i])
	{
		free(values.env[i]);
		i++;
	}
	free(values.env);
}
