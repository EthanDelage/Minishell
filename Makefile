NAME		=		minishell

#######################
#	DIR
#######################

SRC_DIR		=		src/

INC_DIR		=		include/

BUILD_DIR	=		.build/

LIBFT_DIR	=		libft/

#######################
#	FILES
#######################

LIBFT		=		$(LIBFT_DIR)libft.a

SRCS		=		main.c \
					envp/dict.c \
					envp/hashtable.c \
					envp/dict_utils.c \
					envp/hashtable_utils.c \
					envp/hashtable_display.c \
					envp/hashtable_get_array.c \
					parsing/line_lexer/line_lexer.c \
					parsing/line_lexer/token/token_add.c \
					parsing/line_lexer/token/token_clear.c \
					parsing/line_lexer/token/token_utils.c \
					parsing/cmd_lexer/cmd_lexer.c \
					parsing/cmd_lexer/cmd_token/cmd_arg_utils.c \
					parsing/cmd_lexer/cmd_token/cmd_arg_add.c \
					parsing/cmd_lexer/cmd_token/cmd_token_add.c \
					parsing/cmd_lexer/cmd_token/cmd_token_utils.c \
					parsing/cmd_lexer/cmd_token/cmd_token_redirect_utils.c \
					parsing/cmd_parser/cmd_parser.c \
					parsing/line_parser/line_parser.c \
					parsing/line_parser/error_line_parser.c \
					exec/builtin/builtin_error.c \
					exec/builtin/env/env.c \
					exec/builtin/unset/unset.c \
					exec/builtin/export/export.c \
					exec/builtin/export/export_no_args.c \
					exec/builtin/cd/cd.c \
					exec/builtin/pwd/pwd.c \
					exec/builtin/exit/exit.c \
					exec/builtin/echo/echo.c \
					exec/redirect/redirect_in/redirect_in.c \
					exec/redirect/redirect_out/redirect_out.c \
					exec/redirect/append_out/append_out.c \
					exec/redirect/here_doc/here_doc.c \
					exec/redirect/here_doc/here_doc_utils.c \
					exec/redirect/redirect.c \
					exec/redirect/redirect_utils.c \
					exec/redirect/here_doc/replace_here_doc.c \
					exec/router/router.c \
					exec/router/router_utils.c \
					parsing/replace/replace.c \
					parsing/replace/replace_cmd_utils.c \
					parsing/replace/split_arg_utils.c \
					parsing/replace/replace_env.c \
					parsing/replace/replace_ret_value.c \
					parsing/replace/replace_quotes.c \
					parsing/analyser/analyser.c \
					exec/exec.c \
					exec/exec_pipe.c \
					exec/exec_cmd.c \
					exec/exec_utils.c \
					exec/exec_subshell.c \

OBJS		=		$(addprefix $(BUILD_DIR), $(SRCS:.c=.o))

DEPS		=		$(OBJS:.o=.d)

#######################
#	COMPILATIONS
#######################

CFLAGS		=		-Wall -Werror -Wextra #-fsanitize=address

DFLAGS		=		-MMD -MP

LFLAGS		=		-L $(LIBFT_DIR) -lft -lreadline

IFLAGS		=		-I $(INC_DIR) -I $(LIBFT_DIR)includes

#######################
#	RULES
#######################


all:				$(NAME)

-include			$(DEPS)

$(NAME):			$(LIBFT) $(OBJS)
					$(CC) $(OBJS) $(LFLAGS) -o $@ -g3 #-fsanitize=address


$(LIBFT):			FORCE
					$(MAKE) all -C $(LIBFT_DIR)

FORCE:

$(BUILD_DIR)%.o:	$(SRC_DIR)%.c
					mkdir -p $(shell dirname $@)
					$(CC) $(CFLAGS) $(DFLAGS) $(IFLAGS) -c $< -o $@ -g3

clean:
					$(MAKE) clean -C $(LIBFT_DIR)
					$(RM) $(OBJS) $(DEPS)

fclean:
					$(MAKE) fclean -C $(LIBFT_DIR)
					$(RM) $(OBJS) $(DEPS) $(NAME)

re:					fclean
					$(MAKE)

.PHONY:				all clean fclean re FORCE
