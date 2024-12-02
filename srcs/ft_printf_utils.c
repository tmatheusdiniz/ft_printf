/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:15:47 by mreinald          #+#    #+#             */
/*   Updated: 2024/11/22 22:16:39 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_numsize(long long n)
{
	int	count;

	count = 1;
	while (n > 9)
	{
		n /= 10;
		count ++;
	}
	return (count);
}

void	ft_putnbr_base(unsigned long long n, char *base, int *i)
{
	unsigned long long	base_size;

	base = HEXBASE;
	base_size = ft_strlen(base);
	while (n >= base_size)
		ft_putnbr_base (n / base_size, base, i);
	ft_putchar(base[n % base_size]);
	(*i)++;
}
