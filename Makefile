#Exit
NAME		= 	minishell

#Sources
SRCS		= 	minishell.c \
				ms_startup.c \
				ms_string_functions.c \
				ms_parsing_functions.c \
				check_line.c \
				tokenize.c \
				errors_management.c \
				list_clear.c \
				list_data.c \
				expand.c \
				b_pwd.c \
				b_cd.c \
				b_echo.c \
				b_export.c \
				b_unset.c \
				b_exit.c \
				b_redirs.c \
				unquoting.c \
				list_to_array.c \
				builtins.c \
				ms_execute.c \
				exec_functions.c \
				exec_lib_functions.c \
				exec_aux_functions.c \
				signals.c \
				ms_exec_functions.c \
				ms_wideuse_values.c \
				heredoc.c \
				exec_commands.c \
				ms_redir.c \
				ms_redir_type.c \
				expand_aux.c \
				b_redirs_inout.c 

OBJS		= 	$(SRCS:.c=.o)

#Bonus
# NAME_BONUS	= 	checker
# BONUS_SRCS	= 	src/checker_bonus.c \


# BONUS_OBJS	= 	$(BONUS_SRCS:.c=.o)

#Compilation
# Linking: option -r to ensure that if the library (.a) file already exists, 
# it will be replaced. The command option -c should be used so that if the 
# file doesn’t exist, it will be created.
AR			=	ar -rcs
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g3 -fsanitize=address
READLFLAG	=	-lreadline #-L /Users/$(USER)/.brew/opt/readline/lib

#Erase
RM			= 	rm -rf

# Libft
LIBFT				=	libft.a
LIBFT_SRC			=	./libft/

#Default target
all:	$(NAME)

$(LIBFT):
			@make -C $(LIBFT_SRC)

$(NAME):	$(LIBFT) $(OBJS)
			$(CC) $(CFLAGS) $(READLFLAG) $(OBJS) $(LIBFT_SRC)$(LIBFT) -o $(NAME)

# bonus:		$(LIBFT) $(BONUS_OBJS)
# 			$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT_SRC)$(LIBFT) -o $(NAME_BONUS)

clean:
			$(RM) $(OBJS)
#			$(RM) $(OBJS) $(BONUS_OBJS) $(NAME_BONUS)

#Cleaning objects and executable 
fclean:		clean
			$(RM) $(NAME)
			@make -C $(LIBFT_SRC) fclean

#Cleaning all and then compilation
re:			fclean all

#Exectute no matter name is
.PHONY: all bonus clean fclean re