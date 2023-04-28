<<<<<<< HEAD
RED = \033[1;31m
BLUE = \033[1;35m
GREEN = \033[1;32m
DEFAULT = \033[0m
NAME		=	minishell
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -I/goinfre/mqaos/.brew/opt/readline/include -g -fsanitize=address
RM			=	rm -rf
HEADER		=	minishell.h
SOURCE		=	lsttools/lst_all_cmd.c \
				lsttools/lst_cmd.c \
				lsttools/lst_fd.c \
				lsttools/ft_strjoin_char.c \
				lsttools/ft_strdub_mini.c \
				parcing/readline.c \
				parcing/minishell_tools.c \
				parcing/replace_env_var.c \
				parcing/replace_env_var_2.c \
				parcing/creatfile.c \
				parcing/convert_to_char_d.c \
				parcing/parcing_tools.c \
				parcing/parcing_tools_2.c \
				minishell.c
				builtin.c\
	 			ft_split.c list_tools.c newRealease.c ft_echo.c ft_chdir.c ft_exit.c\
				ft_pwd.c ft_export.c  exp_option.c ft_unset.c ft_ex_cmd.c

OBJS		=	$(SOURCE:.c=.o)
LIBFT		= ./libft/libft.a


%.o: %.c
				@${CC} ${FLAGS} -c $< -o $@

$(NAME):		$(OBJS) $(LIBFT) 
				@$(CC) $(OBJS) -o $(NAME) -L/goinfre/mqaos/.brew/opt/readline/lib -L./libft -lft -lreadline -lhistory -g -fsanitize=address
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

=======
RED = \033[1;31m
BLUE = \033[1;35m
GREEN = \033[1;32m
DEFAULT = \033[0m
NAME		=	minishell
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -I/goinfre/mbousouf/.brew/opt/readline/include -g -fsanitize=address
RM			=	rm -rf
HEADER		=	minishell.h
SOURCE		=	listtools.c readline.c minishell_tools.c replace_env_var.c creatfile.c convert_to_char_d.c builtin.c\
	 			ft_split.c list_tools.c newRealease.c ft_echo.c ft_chdir.c ft_exit.c\
				ft_pwd.c ft_export.c  exp_option.c ft_unset.c ft_ex_cmd.c

OBJS		=	$(SOURCE:.c=.o)
LIBFT		= ./libft/libft.a
%.o: %.c 
				@${CC} ${FLAGS} -c $< -o $@

$(NAME):		$(OBJS) $(LIBFT) 
				@$(CC) $(OBJS) -o $(NAME) -L/goinfre/mbousouf/.brew/opt/readline/lib -L./libft -lft -lreadline -lhistory  -g -fsanitize=address
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

>>>>>>> mbousouf
.PHONY:		all clean fclean re