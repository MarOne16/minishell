RED = \033[1;31m
BLUE = \033[1;35m
GREEN = \033[1;32m
DEFAULT = \033[0m
NAME		=	minishell
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror 
RM			=	rm -rf
HEADER		=	minishell.h
SOURCE		=	Qaos/listtools.c Qaos/readline.c Qaos/minishell_tools.c\
				ft_split.c list_tools.c newRealease.c builtin.c
OBJS		=	$(SOURCE:.c=.o)
LIBFT = libft/libft.a
%.o: %.c 
				@${CC} ${FLAGS} -c $< -o $@

$(NAME):		$(OBJS)
				@$(CC) $(OBJS) -o $(NAME) -lreadline 
				@echo "$(GREEN)$(NAME) Created √$(DEFAULT)"

all:			$(NAME)

clean:
				@$(RM) $(OBJS)
				@echo "$(BLUE)Files.o Deleted x$(DEFAULT)"

fclean:			clean
				@$(RM) $(NAME)
				@echo "$(RED)Files.o & Execution deleted X$(DEFAULT)"
LIBFT_A : LIBFT
	make -C libft

re:				fclean all

.PHONY:		all clean fclean re