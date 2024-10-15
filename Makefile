##########################################
# PROBAR ESTO ############################
#.SILENT:clean to silence an instruction #
##########################################

######################
#     Variables      #
######################

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a
LIBFT_FLAGS = -L$(LIBFT_PATH) -lft
READLINE = -lreadline
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

######################
#      SOURCES       #
######################

SRCS_MINISHELL		=	main.c 
SRCS_TOKEN			= 	token_main.c token_list.c dollar_handler.c tokenize_spaces.c
SRCS_PARSER			=	parser_main.c parser_list.c parser_redir_handler.c struct_redir_handler.c
SRCS_ENVP			=	envp_list.c envp_utils.c update_envp.c  envp_shlvl.c
SRCS_SIGNAL			=	signal_handler.c
SRCS_FREE			=	free_basic.c free_structure.c
SRCS_BUILTIN		=	ft_echo.c ft_pwd.c ft_envp.c ft_export.c ft_exit.c  ft_cd.c ft_cd_aux.c ft_unset.c
SRCS_UTILS			=	ft_utils.c ft_error.c ft_utils2.c ft_malloc_handler.c ft_file_handler.c
SRCS_EXECUTE		=	execute_main.c redirection_handler.c heredoc.c builtin_handler.c command_handler.c redir_builtins.c
DIR_MINISHELL		=	$(addprefix ./src/, $(SRCS_MINISHELL)) 
DIR_TOKEN			=	$(addprefix ./src/token/, $(SRCS_TOKEN))
DIR_UTILS			=	$(addprefix ./src/utils/, $(SRCS_UTILS))
DIR_PARSER			=	$(addprefix ./src/parser/, $(SRCS_PARSER))
DIR_ENVP			=	$(addprefix ./src/envp/, $(SRCS_ENVP))
DIR_SIGNAL			=	$(addprefix ./src/signal/, $(SRCS_SIGNAL))
DIR_FREE			=	$(addprefix ./src/free/, $(SRCS_FREE))
DIR_BUILTIN			=	$(addprefix ./src/builtins/, $(SRCS_BUILTIN))
DIR_EXECUTE			=	$(addprefix ./src/execute/, $(SRCS_EXECUTE))
OBJS				= 	$(DIR_MINISHELL:.c=.o) $(DIR_TOKEN:.c=.o) $(DIR_UTILS:.c=.o) $(DIR_ENVP:.c=.o) $(DIR_SIGNAL:.c=.o) $(DIR_FREE:.c=.o) \
						$(DIR_PARSER:.c=.o) $(DIR_EXECUTE:.c=.o) $(DIR_BUILTIN:.c=.o)
######################
#       COLORS       #
######################

RED					=	\033[91m
YELLOW				=	\033[93m
GREEN				=	\033[92m
NO_COLOR			=	\033[0m

######################
#    INSTRUCTIONS    #
######################

all: $(LIBFT) $(NAME)
 
$(NAME): $(OBJS) 
	@echo "$(YELLOW)[COMPILING MINISHELL]$(NO_COLOR)"
	 $(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_FLAGS) $(READLINE)
	@echo "$(GREEN)[COMPILED MINISHELL]$(NO_COLOR)"
 

$(LIBFT):
	@echo "$(YELLOW)[COMPILING LIBFT]$(NO_COLOR)"
	make -s -C $(LIBFT_PATH) all
	@echo "$(GREEN)[COMPILED LIBFT]$(NO_COLOR)"


fclean: clean
	@make -s -C $(LIBFT_PATH) fclean
	@$(RM) $(NAME)
	@echo "$(RED)[DELETED]$(NO_COLOR)"

clean:	
	@make -s -C $(LIBFT_PATH) clean
	@$(RM) $(OBJS) $(OBJS_BONUS)

re: fclean all

.PHONY: all clean fclean re