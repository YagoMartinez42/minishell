/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:37:06 by samartin          #+#    #+#             */
/*   Updated: 2023/10/24 16:05:47 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	pf_recur_drop(long num, char *base, int blen)
{
	int	count;

	count = 0;
	if (num >= blen)
		count += pf_recur_drop(num / blen, base, blen);
	count += write(1, &base[num % blen], 1);
	return (count);
}

int	pf_putnum_b(long num, char *base, char mode)
{
	int	blen;
	int	count;

	count = 0;
	if (num == 0xFFFFFFFF && mode == 1)
		return (write(1, "-2147483648", 11));
	else if (num < 0 && mode == 1)
	{
		count = write(1, "-", 1);
		num = -num;
	}
	blen = 0;
	while (base[blen])
		blen++;
	count += pf_recur_drop(num, base, blen);
	return (count);
}

unsigned int	pf_putaddr(void *addr)
{
	unsigned int	count;

	count = write (1, "0x", 2);
	count += pf_putnum_b((long)addr, "0123456789abcdef", 0);
	return (count);
}
