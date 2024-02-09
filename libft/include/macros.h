#ifndef MACROS_H
# define MACROS_H

# define TRUE 1
# define FALSE 0
# define ERROR -1

// for get_next_line
# define BUFFER_PARSED -2
# define NEW_BUFFER -1
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
// #  define BUFFER_SIZE 5
# endif

// colors

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

#endif
