/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 16:28:36 by slabelle          #+#    #+#             */
/*   Updated: 2020/04/05 17:38:53 by slabelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static int			printf_parse(const char *format, va_list *ap,
					t_flags *flags, t_specifiers *specs)
{
	int				printed;

	printed = 0;
	specs->j = specs->i;
	while (format[++(specs->j)])
		if (!(ft_strchr(".-0123456789*#+ ", format[specs->j])))
			break ;
	while (++(specs->i) < specs->j
		&& !(ft_strchr(".123456789*", format[specs->i])))
		if (format[specs->i] == '-')
			flags->minus = 1;
		else if (format[specs->i] == '0' && flags->minus == 0)
			flags->zero = 1;
	if (++(specs->i) < specs->j && ft_strchr("123456789*", format[specs->i]))
		if (specs->width = printf_width(format, specs) < 0)
			exit(-1);
	if (format[specs->i] == '.')
		flags->dot = 1;
	if (++(specs->i) < specs->j && ft_strchr("123456789*", format[specs->i]))
		if (specs->precision = printf_precision(format, specs) < 0)
			exit(-1);
	if (ft_strchr("cspxXdiu%", format[specs->i]))
		specs->letter = format[specs->i];
	return (printed);
}

static int			printf_input(const char *format, va_list *ap)
{
	int				i;
	int				printed;
	t_flags			*flags;
	t_specifiers	*specs;

	i = -1;
	printed = 0;
	while (format[++i])
		if (format[i] != '%')
			printed += ft_putchar_fd(format[i], 1);
		else if (format[i] == '%' && format[i + 1])
		{
			if (!(flags = printf_init_flags()))
				exit(-1);
			if (!(specs = printf_init_specs()))
				exit(-1);
			specs->i = i;
			printed += printf_parse(format, &ap, flags, specs);
			i = specs->i;
			free(flags);
			free(specs);
		}
	return (printed);
}

int					ft_printf(const char *format, ...)
{
	const char		*format_cpy;
	va_list			ap;
	int				printed;

	if (!(format_cpy = ft_strdup(format)))
		return (0);
	va_start(ap, format);
	printed = 0;
	printed += printf_input(format_cpy, &ap);
	free(format_cpy);
	va_end(ap);
	return (printed);
}
