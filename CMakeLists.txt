cmake_minimum_required(VERSION 3.21)
project(Minishell C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(minishell src/main.c src/exec/builtin/cd/cd.c src/exec/builtin/echo/echo.c src/exec/builtin/env/env.c src/exec/builtin/exit/exit.c src/exec/builtin/export/export.c src/exec/builtin/pwd/pwd.c src/exec/builtin/unset/unset.c include/envp.h src/envp/dict.c src/envp/hashmap.c src/envp/dict_utils.c src/envp/hashmap_utils.c)
