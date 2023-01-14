cmake_minimum_required(VERSION 3.21)
project(Minishell C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(minishell
        libft/includes/libft.h
        src/main.c
        include/envp.h
        src/envp/dict.c
        src/envp/hashtable.c
        src/envp/dict_utils.c
        src/envp/hashtable_utils.c src/envp/hashtable_display.c src/envp/hashtable_get_array.c libft/srcs/string/ft_strcpy.c src/exec/builtin/unset/unset.c)
