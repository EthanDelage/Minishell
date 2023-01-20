cmake_minimum_required(VERSION 3.21)
project(Minishell C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(minishell src/main.c include/envp.h src/envp/dict.c src/envp/dict_utils.c include/line_lexer.h src/parsing/line_lexer/line_lexer.c src/parsing/line_lexer/token/token_add.c src/parsing/line_lexer/token/token_add.c src/parsing/line_lexer/token/token_clear.c src/parsing/line_lexer/token/token_utils.c include/token.h include/cmd_token.h src/parsing/line_parser/line_parser.c include/parser.h src/parsing/line_parser/error_line_parser.c)
