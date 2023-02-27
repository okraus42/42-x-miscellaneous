/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 13:43:29 by okraus            #+#    #+#             */
/*   Updated: 2023/02/27 19:12:59 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>

typedef struct s_output
{
	char	*string;
	int		len;
	int		precision;
	int		padsize;
	int		dash;
	int		zero;
	int		period;
	int		hash;
	int		space;
	int		plus;
	char	type;
	int		base;
}			t_output;

int			ft_printf(int fd, const char *s, ...);
void		ft_putstuff(va_list arg, const char *s, int *q, t_output *t);
void		ft_writestuff(int fd, const char *s, int *q);
int			ft_putchar_fd(char c, int fd, t_output *t);
int			ft_print_char_fd(char s, int fd, t_output *t);
char		*ft_string_pointer(void *mem);
int			ft_putpointer_fd(void *mem, int fd, t_output *t);
int			ft_print_pointer_fd(void *mem, int fd);
size_t		ft_strlen(const char *s);
int			ft_putstring_fd(char *s, int fd, t_output *t);
int			ft_print_string_fd(char *s, int fd, t_output *t);
int			ft_putunsigned_fd(unsigned int u, int fd, t_output *t);
int			ft_print_unsigned_fd(unsigned int u, int fd, t_output *t);
char		*ft_string_unsigned(unsigned int u);
int			ft_putinteger_fd(int d, int fd, t_output *t);
int			ft_print_integer_fd(int d, int fd, t_output *t);
char		*ft_string_integer(int d);
int			ft_puthexabig_fd(unsigned int h, int fd, t_output *t);
int			ft_print_hexabig_fd(unsigned int h, int fd, t_output *t);
char		*ft_string_hexabig(unsigned int h);
int			ft_puthexasmall_fd(unsigned int h, int fd, t_output *t);
int			ft_print_hexasmall_fd(unsigned int h, int fd, t_output *t);
char		*ft_string_hexasmall(unsigned int h);
void		ft_initialise_struct(t_output *t);
void		ft_dash_struct(t_output *t, int n);
void		ft_prefill_struct(t_output *t, const char *s);
int			ft_get_num(t_output *t, const char *s, int i);
char		*ft_strjoin_freeleft(char *s1, char const *s2);
char		*ft_strjoin_freeright(char const *s1, char *s2);
char		*ft_padchar(char *s, int len, t_output *t);
char		*ft_padint(char *s, t_output *t);
char		*ft_precint(char *s, t_output *t);
int			ft_putbasebig_fd(unsigned int b, int fd, t_output *t);
int			ft_print_basebig_fd(unsigned int b, int fd, t_output *t);
char		*ft_string_basebig(unsigned int b, t_output *t);
int			ft_putbinocthex_fd(void *b, int fd, t_output *t);
int			ft_print_binocthex_fd(unsigned char b, int fd, t_output *t);
char		*ft_string_binocthex(unsigned char b, t_output *t);
int			ft_putcolour_fd(int fd, t_output *t);
int			ft_print_colour_fd(int fd, t_output	*t);

#endif
