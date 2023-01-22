cmake_minimum_required(VERSION 3.21)
project(Minishell C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(minishell
        libft/includes/libft.h
        libft/includes/get_next_line.h
        libft/srcs/char/ft_isalnum.c
        libft/srcs/char/ft_isalpha.c
        libft/srcs/char/ft_isascii.c
        libft/srcs/char/ft_isdigit.c
        libft/srcs/char/ft_isprint.c
        libft/srcs/char/ft_issign.c
        libft/srcs/char/ft_isspace.c
        libft/srcs/char/ft_tolower.c
        libft/srcs/char/ft_toupper.c
        libft/srcs/convert/ft_atoi.c
        libft/srcs/convert/ft_itoa.c
        libft/srcs/fd/ft_putchar_fd.c
        libft/srcs/fd/ft_putendl_fd.c
        libft/srcs/fd/ft_putnbr_fd.c
        libft/srcs/fd/ft_putstr_fd.c
        libft/srcs/get_next_line/get_next_line.c
        libft/srcs/get_next_line/get_next_line_utils.c
        libft/srcs/list/ft_lstadd_back.c
        libft/srcs/list/ft_lstadd_front.c
        libft/srcs/list/ft_lstclear.c
        libft/srcs/list/ft_lstdelone.c
        libft/srcs/list/ft_lstiter.c
        libft/srcs/list/ft_lstlast.c
        libft/srcs/list/ft_lstmap.c
        libft/srcs/list/ft_lstnew.c
        libft/srcs/list/ft_lstsize.c
        libft/srcs/memory/ft_bzero.c
        libft/srcs/memory/ft_calloc.c
        libft/srcs/memory/ft_memchr.c
        libft/srcs/memory/ft_memcmp.c
        libft/srcs/memory/ft_memcpy.c
        libft/srcs/memory/ft_memmove.c
        libft/srcs/memory/ft_memset.c
        libft/srcs/stdout/ft_putchar.c
        libft/srcs/stdout/ft_putendl.c
        libft/srcs/stdout/ft_putnbr.c
        libft/srcs/stdout/ft_putstr.c
        libft/srcs/string/ft_split.c
        libft/srcs/string/ft_strchr.c
        libft/srcs/string/ft_strdup.c
        libft/srcs/string/ft_striteri.c
        libft/srcs/string/ft_strjoin.c
        libft/srcs/string/ft_strlcat.c
        libft/srcs/string/ft_strlcpy.c
        libft/srcs/string/ft_strlen.c
        libft/srcs/string/ft_strmapi.c
        libft/srcs/string/ft_strncmp.c
        libft/srcs/string/ft_strnstr.c
        libft/srcs/string/ft_strrchr.c
        libft/srcs/string/ft_strtrim.c
        libft/srcs/string/ft_substr.c
        src/main.c
        include/envp.h
        src/envp/dict.c
        src/envp/hashtable.c
        src/envp/dict_utils.c
        src/envp/hashtable_utils.c src/envp/hashtable_display.c src/envp/hashtable_get_array.c src/parsing/replace/replace.c libft/srcs/string/ft_strncpy.c)
