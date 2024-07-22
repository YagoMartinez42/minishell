/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:44:40 by samartin          #+#    #+#             */
/*   Updated: 2023/10/24 15:35:29 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int	process_data(const char ftype, va_list f_args)
{
	unsigned int	wrtn;

	if (ftype == 'c')
		wrtn = pf_putchar(va_arg(f_args, int));
	else if (ftype == 's')
		wrtn = pf_putstr(va_arg(f_args, char *));
	else if (ftype == 'p')
		wrtn = pf_putaddr(va_arg(f_args, void *));
	else if (ftype == 'd' || ftype == 'i')
		wrtn = pf_putnum_b(va_arg(f_args, int), "0123456789", 1);
	else if (ftype == 'u')
		wrtn = pf_putnum_b(va_arg(f_args, unsigned int), "0123456789", 0);
	else if (ftype == 'x')
		wrtn = pf_putnum_b(va_arg(f_args, unsigned int), "0123456789abcdef", 0);
	else if (ftype == 'X')
		wrtn = pf_putnum_b(va_arg(f_args, unsigned int), "0123456789ABCDEF", 0);
	else
		wrtn = pf_putchar((int)ftype);
	return (wrtn);
}

int	ft_printf(const char *format, ...)
{
	unsigned int	i;
	unsigned int	chr_cnt;
	va_list			f_args;

	va_start(f_args, format);
	i = 0;
	chr_cnt = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			chr_cnt += process_data(format[i + 1], f_args);
			i++;
		}
		else
		{
			write (1, &format[i], 1);
			chr_cnt++;
		}
		i++;
	}
	va_end(f_args);
	return ((int)chr_cnt);
}
