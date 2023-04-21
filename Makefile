RED = \033[1;31m
BLUE = \033[1;35m
GREEN = \033[1;32m
DEFAULT = \033[0m
NAME		=	minishell
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror #-g -fsanitize=address
RM			=	rm -rf
HEADER		=	minishell.h
SOURCE		=	listtools.c readline.c minishell_tools.c replace_env_var.c creatfile.c convert_to_char_d.c builtin.c\
	 			ft_split.c list_tools.c newRealease.c ft_echo.c ft_chdir.c ft_exit.c\
				ft_pwd.c ft_export.c  exp_option.c ft_unset.c

OBJS		=	$(SOURCE:.c=.o)
LIBFT		= ./libft/libft.a
%.o: %.c 
				@${CC} ${FLAGS} -c $< -o $@

$(NAME):		$(OBJS) $(LIBFT) 
				@$(CC) $(OBJS) -o $(NAME) -L ./libft -lft -lreadline #-g -fsanitize=address
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