#ifndef LIBFT_H
# define LIBFT_H

# include "included_ext_libs.h"
# include "macros.h"

typedef struct s_file_info
{
	int					*cols;
	int					rows;
	char				sep;
	int					file_size;
}						t_file_info;

typedef struct s_list
{
	void				*content;
	struct s_list		*next;
}						t_list;

typedef struct s_list_dc
{
	void				*content;
	struct s_list_dc	*next;
	struct s_list_dc	*prev;
}						t_list_d;

typedef struct s_base_info
{
	char				*base;
	size_t				base_len;
}						t_base_info;

typedef struct s_split_sq
{
	int					i_str;
	size_t				i_num_substr;
	size_t				substr_len;
	char				**res;
	char				c;
	const char			*s;
}						t_split_sq;

typedef struct s_arr_char_key_info
{
	int					arr_len;
	char				*val;
	int					key_len;
	int					key_occ_n;
	char				**cpy;
}						t_arr_char_key_info;

typedef struct s_ins_repl_str
{
	char				*org_str;
	char				*repl_str;
	char				*ins_str;
	int					search_start_index;
}						t_ins_repl_str;

/* ascci char checks n manip */

int						ft_isprint(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isalpha(int c);
int						ft_toupper(int c);
int						ft_tolower(int c);
int						ft_isspace(char c);

/* str search n compare */

size_t					ft_strlen(const char *s);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
ssize_t					ft_str_chr_index(const char *s, int c);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strnstr(const char *big, const char *little,
							size_t len);
int						ft_str_cont_duplic(const char *str);
int						ft_str_cont_chars(const char *str, const char *set);
int						str_are_equal(const char *s1, const char *s2);
int						str_is_empty(const char *str);
int						str_contains_str_index(const char *big,
							const char *little);

/* str manip */

size_t					ft_strlcpy(char *dst, const char *src, size_t size);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
char					*ft_strdup(const char *s);
char					*ft_str_n_dup(const char *s, int n);
int						ft_str_n_dup_int(const char *s, int n, char **res);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_str_n_join(char const *s1, char const *s2, int n);
int						ft_str_n_join_int(char const *s1, char const *s2, int n,
							char **res);
int						ft_join_n_str(char **res, int num, ...);
char					*ft_strtrim(char const *s1, char const *set);
char					*ft_strmapi(char const *s, char (*f)(unsigned int,
								char));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
int						split_str_str_after_index(char const *s,
							char const *split_at, char ***res, int index);
int						ins_replace_str_after_index(char **res,
							t_ins_repl_str replace_info);
int						rem_str_after_index(char **res,
							t_ins_repl_str replace_info);
int						remove_spaces_inplace(char **str);
bool					str_only_spaces(char *str);

/* split */

int						malloc_error_free(char **res, size_t i_num_substr,
							size_t substr_len);
char					**ft_split(char const *s, char c);
char					**ft_split_str(char const *s, char const *split_at);
size_t					ft_split_num_substr(char const *s, char c);
size_t					ft_split_num_substr_sq(char const *s, char c);
char					**ft_split_single_quotes(char const *s, char c);

/* mem stuff */

void					*ft_memset(void *s, int c, size_t n);
void					*ft_memcpy(void *dest, const void *src, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memmove(void *dest, const void *src, size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
void					*ft_calloc(size_t nmemb, size_t size);
void					*ft_bzero(void *s, size_t n);

/* linked lists */

t_list					*ft_lstnew(void *content);
void					ft_lstadd_front(t_list **lst, t_list *new);
void					ft_lstadd_back(t_list **lst, t_list *new);
int						ft_lstsize(t_list *lst);
t_list					*ft_lstlast(t_list *lst);
void					ft_lstdelone(t_list *lst, void (*del)(void *));
void					ft_lstclear(t_list **lst, void (*del)(void *));
void					ft_lstiter(t_list *lst, void (*f)(void *));
t_list					*ft_lstmap(t_list *lst, void *(*f)(void *),
							void (*del)(void *));

/* double circular linked list */

t_list_d				*dc_lst_new(void *content);

void					dc_lst_print_whole(t_list_d *lst_ptr,
							const char *longShort, const char *type);
void					dc_lst_print_one_str_long(void *lst_ptr_void);
void					dc_lst_print_one_str_short(void *lst_ptr_void);
void					dc_lst_print_one_int_long(void *lst_ptr_void);
void					dc_lst_print_one_int_short(void *lst_ptr_void);

void					dc_lst_print_sep(void);

void					dc_lst_add_back(t_list_d **lst, t_list_d *new);
void					dc_lst_add_front(t_list_d **lst, t_list_d *new);
int						dc_lst_size(t_list_d *lst);
void					dc_lst_clear(t_list_d **lst, void (*del)(void *));
void					dc_lst_del_one(t_list_d *lst, void (*del)(void *));
void					dc_lst_iter_node(t_list_d *lst, void (*f)(void *));
void					dc_lst_iter_content(t_list_d *lst, void (*f)(void *));
t_list_d				*dc_lst_map(t_list_d *lst, void *(*f)(void *),
							void (*del)(void *));
int						dc_lst_exactly_one(t_list_d *lst_ptr);
t_list_d				*dc_lst_pop(t_list_d **lst);
int						dc_lst_exactly_one(t_list_d *lst_ptr);
int						dc_lst_exactly_two(t_list_d *lst_ptr);

t_list_d				*dc_lst_swap(t_list_d **lst);

/* double linked list non circular*/

t_list_d				*d_lst_new(void *content);
t_list_d				*d_lst_last(t_list_d *lst);
void					d_lst_add_back(t_list_d **lst, t_list_d *new);
void					d_lst_add_front(t_list_d **lst, t_list_d *new);
void					d_lst_clear(t_list_d **lst, void (*del)(void *));
void					d_lst_del_one(t_list_d *lst, void (*del)(void *));
int						d_lst_exactly_one(t_list_d *lst_ptr);
int						d_lst_exactly_two(t_list_d *lst_ptr);
int						d_lst_size(t_list_d *lst);
t_list_d				*d_lst_pop(t_list_d **lst);
t_list_d				*d_lst_pop_n(t_list_d **lst, int n);
t_list_d				*d_lst_pop_current(t_list_d **lst);
t_list_d				*d_lst_swap(t_list_d **lst);
t_list_d				*d_lst_map(t_list_d *lst, void *(*f)(void *),
							void (*del)(void *));
void					d_lst_iter_content(t_list_d *lst, void (*f)(void *));
void					d_lst_iter_node(t_list_d *lst, void (*f)(void *));
bool					d_lst_is_first(t_list_d *lst);
bool					d_lst_is_last(t_list_d *lst);

/* output */

void					ft_putchar_fd(char c, int fd);
size_t					ft_putchar_fd_len(char c, int fd);
void					ft_putstr_fd(char *s, int fd);
size_t					ft_putstr_fd_len(char *s, int fd);
size_t					ft_putstr_fd_len_only_print(char *s, int fd);
void					ft_putendl_fd(char *s, int fd);
void					ft_putnbr_fd(int n, int fd);
size_t					ft_putnbr_base_fd_l(int fd, long nbr, const char *base);
size_t					ft_putnbr_base_fd_ul(int fd, unsigned long nbr,
							const char *base);
size_t					ft_putnbr_base_check(const char *base,
							t_base_info *base_info);

/* atoi itoa */

int						ft_atoi(const char *nptr);
ssize_t					ft_atoi_base_l(const char *nptr, const char *base);
int						ft_atoi_secure(const char *nptr);

char					*ft_itoa(int n);

/* int arr */

size_t					ft_arr_set_int(int *arr, size_t size, int num);
int						int_arr_int_index(int *arr, int search, int arr_len);
void					print_int_arr(int *arr, int num);

/* string array */
size_t					ft_arr_len_char(char **arr);
char					**ft_arr_cpy_char(char **arr, int num);
void					free_str_arr_null(char **str_arr);
void					free_str_arr(char **str_arr, int num);
void					print_str_arr_null(char **arr);
void					print_str_arr(char **arr, int num);
int						ft_arr_char_occ_num_n(char **arr, char *key);
char					**ft_arr_char_rem_n(char **arr, char *key);
char					**ft_arr_char_add(char **arr, char *val);
char					**ft_arr_cpy_char_null(char **arr);
char					**ft_arr_char_add_replace_n(char **arr, char *val);
char					*ft_arr_char_get_val(char **arr, char *key);

/* math */

int						ft_pow(int nb, int power);
int						ft_abs(int nb);

/* files */

int						count_lines_filename(char *filename);
int						count_lines_size_filename(char *filename,
							t_file_info *file_info);
int						count_lines_fd(int fd);
int						count_lines_size_fd(int fd, t_file_info *file_info);
void					free_file_info_ptr(t_file_info *file_info);
void					free_file_info(t_file_info file_info);
int						count_cols_per_line_fd(int fd, t_file_info *file_info);
int						count_cols_per_line_filename(char *filename,
							t_file_info *file_info);
int						get_file_size_filename(char *filename);
int						get_file_size_fd(int fd);
int						read_whole_file(int fd, char **res);

/* free */

int						free_char_variadic_code(int code, int num, ...);
int						free_char_variadic_msg(char *msg, int num, ...);

#endif