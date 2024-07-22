/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:28:48 by samartin          #+#    #+#             */
/*   Updated: 2023/10/24 15:36:21 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int				ft_printf(const char *format, ...);
unsigned int	pf_putchar(int chr);
unsigned int	pf_putstr(char *str);
int				pf_putnum_b(long num, char *base, char mode);
unsigned int	pf_putaddr(void *addr);
unsigned int	pf_putfloat(double num);
void			*ft_print_memory(void *addr, unsigned int size);

#endif