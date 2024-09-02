/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:24:29 by dyanez-m          #+#    #+#             */
/*   Updated: 2023/09/28 14:19:48 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../libft.h"
# include <unistd.h>

# define HEX_UP "0123456789ABCDEF"
# define HEX_LOW "0123456789abcdef"
# define DECIMAL "0123456789"

int		ft_type(const char *str, va_list args);
int		ft_printf(const char *string, ...);
int		ft_putchar_c(char c);
int		ft_putstr_c(const char *str);
int		ft_putptr_c(void *ptr);
int		ft_putnbr_c(int n);
int		ft_putunbr_c(unsigned int n);
int		ft_puthex_c(unsigned int n, int up);
void	ft_write_ull(unsigned long long p, int base_len, char *base);
int		ft_ulllen_base(unsigned long long n, int base_len);

#endif