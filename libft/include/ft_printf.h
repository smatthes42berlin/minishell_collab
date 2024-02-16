#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "included_ext_libs.h"
# include "macros.h"

int		ft_vdprintf(int fd, const char *format, va_list args);
int		ft_printf(const char *format, ...);
int		ft_printf_fd(int fd, const char *format, ...);
int		ft_printf_to_str(char **res, const char *format, ...);
size_t	handle_p(int fd, va_list args);
size_t	handle_c(int fd, va_list args);
size_t	handle_s(int fd, va_list args);
size_t	handle_d_i(int fd, va_list args);
size_t	handle_u(int fd, va_list args);
size_t	handle_x(int fd, va_list args);
size_t	handle_cap_x(int fd, va_list args);

#endif