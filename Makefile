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
					minishell_utils.c \
					envp/dict.c \
					envp/dict_utils.c \
					envp/dict_sort.c \
					envp/hashtable.c \
					envp/hashtable_utils.c \
					envp/hashtable_get_array.c \
					envp/shlvl.c \
					envp/pwd.c \
					analyser/line_lexer/line_lexer.c \
					analyser/line_lexer/token/token_add.c \
					analyser/line_lexer/token/token_clear.c \
					analyser/line_lexer/token/token_utils.c \
					analyser/cmd_lexer/cmd_lexer.c \
					analyser/cmd_lexer/cmd_token/cmd_arg_utils.c \
					analyser/cmd_lexer/cmd_token/cmd_arg_add.c \
					analyser/cmd_lexer/cmd_token/cmd_token_add.c \
					analyser/cmd_lexer/cmd_token/cmd_token_utils.c \
					analyser/cmd_lexer/cmd_token/cmd_token_redirect_utils.c \
					analyser/cmd_parser/cmd_parser.c \
					analyser/line_parser/line_parser.c \
					analyser/error_syntax.c \
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
					exec/redirect/here_doc/here_doc_get.c \
					exec/redirect/here_doc/here_doc_utils.c \
					exec/redirect/redirect.c \
					exec/redirect/redirect_utils.c \
					exec/redirect/here_doc/replace_here_doc.c \
					exec/router/router.c \
					exec/router/router_utils.c \
					analyser/replace/replace.c \
					analyser/replace/replace_cmd_utils.c \
					analyser/replace/split_arg_utils.c \
					analyser/replace/replace_env.c \
					analyser/replace/replace_env_utils.c \
					analyser/replace/replace_ret_value.c \
					analyser/replace/replace_quotes.c \
					analyser/replace/wildcards/wildcards.c \
					analyser/replace/wildcards/wildcards_utils.c \
					analyser/analyser/analyser.c \
					exec/exec.c \
					exec/exec_pipe.c \
					exec/exec_pipe_utils.c \
					exec/exec_cmd.c \
					exec/exec_cmd_utils.c \
					exec/exec_utils.c \
					exec/exec_subshell.c \
					exec/exec_subshell_utils.c \
					signal/signal.c \
					signal/sig_handler.c \
					signal/termios.c \

OBJS		=		$(addprefix $(BUILD_DIR), $(SRCS:.c=.o))

DEPS		=		$(OBJS:.o=.d)

#######################
#	COMPILATIONS
#######################

CFLAGS		=		-Wall -Werror -Wextra

DFLAGS		=		-MMD -MP

LFLAGS		=		-L $(LIBFT_DIR) -lft -lreadline

IFLAGS		=		-I $(INC_DIR) -I $(LIBFT_DIR)includes

#######################
#	RULES
#######################


all:				$(NAME)

-include			$(DEPS)

$(NAME):			$(LIBFT) $(OBJS)
					$(CC) $(OBJS) $(LFLAGS) $(CFLAGS) -o $@


$(LIBFT):			FORCE
					$(MAKE) all -C $(LIBFT_DIR)

FORCE:

$(BUILD_DIR)%.o:	$(SRC_DIR)%.c
					mkdir -p $(shell dirname $@)
					$(CC) $(CFLAGS) $(DFLAGS) $(IFLAGS) -c $< -o $@

clean:
					$(MAKE) clean -C $(LIBFT_DIR)
					$(RM) $(OBJS) $(DEPS)

fclean:
					$(MAKE) fclean -C $(LIBFT_DIR)
					$(RM) $(OBJS) $(DEPS) $(NAME)

re:					fclean
					$(MAKE)

.PHONY:				all clean fclean re FORCE
