/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:22:05 by mreinald          #+#    #+#             */
/*   Updated: 2024/11/30 13:01:56 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	integer_handler(va_list args, t_flags *flags)
{
	int			count;
	long int	number;

	count = 0;
	number = va_arg(args, int);
	if (flags->left_aligment)
		count += print_int_left_pp(number, flags, flags->precision - 1);
	else if (flags->precision > 0 && flags->width > 0)
		count += print_w_int(number, flags, flags->precision - 1);
	else if (flags->width)
		count += print_w_int(number, flags, flags->precision - 1);
	else if (flags->precision)
	{
		if (flags->precision - 1 == 0 && number == 0)
			return (0);
		count += print_int_p(number, flags->precision - 1,
				flags->space, flags->sign_plus);
	}
	else
		count += ft_putstr(ft_itoa(number));
	return (count);
}

int	print_int_p(int number, int precision, int space, int sign_plus)
{
	int		count;	
	int		size_number;

	count = 0;
	size_number = ft_numsize(number);
	if (number < 0)
		size_number--;
	if (sign_plus && number >= 0 && !space)
		count += ft_putchar('+');
	else if (space && !sign_plus && number >= 0)
		count += ft_putchar(' ');
	if (precision > size_number)
	{
		if (number < 0)
		{
			count += ft_putchar('-');
			number = -number;
		}
		while (precision-- > size_number)
			count += ft_putchar('0');
		count += ft_putnbr(number);
	}
	else
		count += ft_putnbr(number);
	return (count);
}

int	print_zero(int number, int size_number, t_flags *flags)
{
	int	count;

	count = 0;
	if (size_number >= flags->width)
	{
		if (flags->sign_plus && number >= 0)
			count += ft_putchar('+');
		count += ft_putnbr(number);
	}
	else
	{
		if (flags->zero && flags->space && number >= 0 && !flags->sign_plus)
			count += aux_z_space(number, flags->width - 1, TRUE);
		else if (flags->zero && flags->space
			&& (number < 0 || flags->sign_plus))
			count += aux_z_space(number, flags->width, FALSE);
		else if (flags->zero && (!flags->sign_plus || number < 0))
			count += aux_z_plus(number, flags->width, FALSE);
		else if (flags->zero && flags->sign_plus && number >= 0)
			count += aux_z_plus(number, flags->width - 1, TRUE);
		else
			count += aux_zero(number, flags);
	}
	return (count);
}

int	print_w_int(int number, t_flags *flags, int precision)
{
	int	count;
	int	size_number;

	count = 0;
	size_number = ft_numsize(number);
	if (flags->left_aligment || precision > 0)
		return (print_aux_w(number, flags, precision, size_number));
	else if (flags->width > 0 && flags->zero)
		count += print_zero(number, ft_numsize(number), flags);
	else
	{
		if (flags->sign_plus || flags->space)
			flags->width --;
		while (flags->width -- > size_number)
			count += ft_putchar(' ');
		if (flags->sign_plus && number >= 0)
			count += ft_putchar('+');
		else if (flags->space && number >= 0)
			count += ft_putchar(' ');
		if (precision == 0 && number == 0)
			return (count += ft_putchar(' '), 0);
		count += ft_putnbr(number);
	}
	return (count);
}

int	print_int_left_pp(int number, t_flags *flags, int precision)
{
	int		count;

	count = 0;
	if (precision > flags->width || (precision && !flags->width))
		count += print_int_p(number, precision,
				flags->space, flags->sign_plus);
	else if (precision && flags->width)
		count += print_w_int(number, flags, precision);
	else if (flags->width > 0 && !precision)
	{
		if (flags->sign_plus && number > 0)
			count += ft_putchar('+');
		if (flags->space)
			count += ft_putchar(' ');
		if (!(precision == 0 && number == 0))
			count += ft_putnbr(number);
		while (flags->width > count)
			count += ft_putchar(' ');
	}
	else
		count += ft_putnbr(number);
	return (count);
}
