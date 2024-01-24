#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "included_ext_libs.h"
# include "macros.h"

typedef struct s_get_next
{
	int		tot_c_read;
	int		i_last_newline;
	char	last_buffer_read[BUFFER_SIZE + 1];
}			t_get_next;

typedef struct s_search_state
{
	int		chars_left;
	int		newline_index;
	char	*tmp_ptr;
	char	*start;
}			t_search_state;

char		*get_next_line(int fd);
int			check_if_newline_in_buffer(t_get_next *gnl_info, char **next_line);
int			process_newline_search_result(t_get_next *gnl_info,
				char **next_line,
				t_search_state search);
void		reset_gnl_static(t_get_next *gnl_info);
char		*reset_gnl_static_null(t_get_next *gnl_info, char **next_line);

size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_str_n_join(char const *s1, char const *s2, int n);
ssize_t		ft_str_chr_index(const char *s, int c);
char		*ft_str_n_dup(const char *s, int n);

#endif
