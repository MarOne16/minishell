RED = \033[1;31m
BLUE = \033[1;35m
GREEN = \033[1;32m
DEFAULT = \033[0m
NAME		=	minishell
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -I/goinfre/mqaos/.brew/opt/readline/include 
RM			=	rm -rf
HEADER		=	minishell.h
SOURCE		=	lsttools/lst_all_cmd.c \
				lsttools/lst_cmd.c \
				lsttools/lst_fd.c \
				lsttools/ft_strjoin_char.c \
				lsttools/ft_strdub_mini.c \
				parsing/readline.c \
				parsing/minishell_tools.c \
				parsing/minishell_tools_3.c \
				parsing/replace_env_var.c \
				parsing/replace_env_var_2.c \
				parsing/creatfile.c \
				parsing/convert_to_char_d.c \
				parsing/parsing_tools.c \
				parsing/parsing_tools_2.c \
				execution/builtin.c \
				execution/ft_split.c \
				execution/list_tools.c \
				execution/newRealease.c \
				execution/ft_echo.c \
				execution/ft_chdir.c \
				execution/ft_chdira.c \
				execution/ft_exit.c \
				execution/ft_pwd.c \
				execution/ft_export.c  \
				execution/ft_export_2.c  \
				execution/exp_option.c \
				execution/ft_unset.c \
				execution/ft_ex_cmd.c \
				execution/sort.c\
				execution/Realeasebeta.c\
				minishell.c \

OBJS		=	$(SOURCE:.c=.o)
LIBFT		= ./libft/libft.a


%.o: %.c
				@${CC} ${FLAGS} -c $< -o $@

$(NAME):		$(OBJS) $(LIBFT) $(HEADER)
				@$(CC) $(OBJS) -o $(NAME) -L/goinfre/mqaos/.brew/opt/readline/lib -L./libft -lft -lreadline -lhistory 
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
	make bonus -C libft

re:				fclean all

.PHONY:		all clean fclean re