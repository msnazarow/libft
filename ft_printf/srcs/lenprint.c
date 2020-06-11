/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenprint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 05:58:09 by sgertrud          #+#    #+#             */
/*   Updated: 2020/06/11 15:44:50 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		c_len(t_format *f, wchar_t temp)
{
	int out;

	out = 0;
	if (f->mod[0] == 'l' && temp > 127)
	{
		while (temp > 0)
		{
			if (temp > (out < 2 ? 32 : 16) && temp < 64)
				out++;
			temp /= 64;
			out++;
		}
		return (out);
	}
	return (1);
}

int		lenprint(t_format *f, va_list arg)
{
	if (f->cv == '%' || f->cv == 'c')
		return (c_len(f, va_arg(arg, wchar_t)));
	if (f->cv == 'i' || f->cv == 'd')
		return (s_len(f, arg));
	if (f->cv == 'u' || f->cv == 'x' || f->cv == 'X' ||
	f->cv == 'o' || f->cv == 'p')
		return (u_len(f, arg));
	if (f->cv == 's')
		return (ft_strlen_cw(f, arg));
	if (f->cv == 'f')
		return (f_len(f, va_arg(arg, double)));
	if (f->cv == 'e')
		return (e_len(f, va_arg(arg, double)));
	if (f->cv == 'g')
		return (g_len(f, va_arg(arg, double)));
	return (-1);
}

int		ft_strlen_cw(t_format *f, va_list arg)
{
	return (f->mod[0] == 'l' ? (ft_strlen_w(va_arg(arg, wchar_t*), f)) :
	(ft_strlen_f(va_arg(arg, char*), f)));
}

int		ft_strlen_f(char *s, t_format *f)
{
	if (!s && f->prec < 6 && f->prec > -1)
		return (0);
	else
		return (ft_strlen(s));
}

size_t	ft_strlen_w(const wchar_t *s, t_format *f)
{
	int len;
	int i;
	int clen;

	if (!s)
		return (6);
	i = -1;
	len = 0;
	while (s[++i] && (f->prec == -1 ? 1 : len < f->prec))
	{
		clen = c_len(f, s[len]);
		len += clen > f->prec ? 0 : clen;
	}
	return (len);
}
