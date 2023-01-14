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
					envp/hashmap.c \
					envp/dict_utils.c \
					parsing/line_lexer/line_lexer.c \
					parsing/line_lexer/token_add.c \
					parsing/line_lexer/token_clear.c \

OBJS		=		$(addprefix $(BUILD_DIR), $(SRCS:.c=.o))

DEPS		=		$(OBJS:.o=.d)

#######################
#	COMPILATIONS
#######################

CFLAGS		=		-Wall -Werror -Wextra

DFLAGS		=		-MMD -MP

LFLAGS		=		-L $(LIBFT_DIR) -lft -lreadline

#######################
#	RULES
#######################


all:				$(NAME)

-include			$(DEPS)

$(NAME):			$(LIBFT) $(OBJS)
					$(CC) $(LFLAGS) $(OBJS) -o $@

$(LIBFT):			FORCE
					$(MAKE) all -C $(LIBFT_DIR)

FORCE:

$(BUILD_DIR)%.o:	$(SRC_DIR)%.c
					mkdir -p $(shell dirname $@)
					$(CC) $(CFLAGS) $(DFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR)includes -c $< -o $@

clean:
					$(MAKE) clean -C $(LIBFT_DIR)
					$(RM) $(OBJS) $(DEPS)

fclean:
					$(MAKE) fclean -C $(LIBFT_DIR)
					$(RM) $(OBJS) $(DEPS) $(NAME)

re:					fclean
					$(MAKE)

.PHONY:				all clean fclean re FORCE
