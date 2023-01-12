NAME		=		minishell

#######################
#	DIR
#######################

SRC_DIR			=		src/

INC_DIR			=		include/

BUILD_DIR		=		.build/

#######################
#	FILES
#######################

SRCS			=		main.c									\
						exec/builtin/cd/cd.c					\

OBJS			=		$(addprefix $(BUILD_DIR), $(SRCS:.c=.o))

DEPS			=		$(OBJS:.o=.d)

#######################
#	COMPILATIONS
#######################

CFLAGS			=		-Wall -Werror -Wextra

DFLAGS			=		-MMD -MP

LFLAGS			=		-lreadline

#######################
#	COMMANDS
#######################

MKDIR			=		mkdir -p

#######################
#	RULES
#######################

-include				$(DEPS)

all:					$(NAME)

$(NAME):				$(OBJS)
						$(CC) $^ -o $@

$(BUILD_DIR)%.o:		$(SRC_DIR)%.c
						mkdir -p $(shell dirname $@)
						$(CC) $(CFLAGS) $(DFLAGS) $(LFLAGS) -I $(INC_DIR) $< -o $@

clean:
						$(RM) $(OBJS) $(DEPS)

fclean:					clean
						$(RM) $(NAME)

re:						fclean
						$(MAKE)

.PHONY:					all clean fclean re
