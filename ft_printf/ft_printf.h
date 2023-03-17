/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:51:19 by ymehlil           #+#    #+#             */
/*   Updated: 2022/11/17 21:43:21 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_printf(const char *s, ...);
int		ft_parse(char s, va_list arg);
int		ft_print_percent(void);
int		ft_print_char(char c);
int		ft_print_str(char *s);
int		len_nb(int nb, int base);
int		ft_print_i(va_list arg);
int		ft_print_u(va_list arg);
int		ft_len_unb(unsigned int nb, int base);
int		ft_print_x(char c, va_list arg);
int		ft_print_ptr(size_t ptr);
int		ft_print_ptr(size_t ptr);

void	ft_ui_putnbr_base_fd(unsigned int nb, char *base, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);

char	*ft_itoa(int n);

size_t	ft_strlen(const char *s);

#endif