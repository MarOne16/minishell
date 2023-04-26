RED = \033[1;31m
BLUE = \033[1;35m
GREEN = \033[1;32m
DEFAULT = \033[0m
NAME		=	minishell
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -I/goinfre/mqaos/.brew/opt/readline/include #-g -fsanitize=address
RM			=	rm -rf
HEADER		=	minishell.h
SOURCE		=	lsttools/lst_all_cmd.c lsttools/lst_cmd.c lsttools/lst_fd.c \
				readline.c minishell_tools.c replace_env_var.c replace_env_var_2.c creatfile.c convert_to_char_d.c parcing_tools.c \
				parcing_tools_2.c minishell.c

OBJS		=	$(SOURCE:.c=.o)
LIBFT		= ./libft/libft.a
%.o: %.c 
				@${CC} ${FLAGS} -c $< -o $@

$(NAME):		$(OBJS) $(LIBFT) 
				@$(CC) $(OBJS) -o $(NAME) -L/goinfre/mqaos/.brew/opt/readline/lib -L./libft -lft -lreadline -lhistory #-g -fsanitize=address
				@echo "$(GREEN)$(NAME) Created √$(DEFAULT)" 


all:			$(NAME) clean

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