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

SRCS_MINISHELL		=	main.c free_handler.c
SRCS_TOKEN			= 	token_main.c token_list.c
SRCS_PARSER			=	parser_main.c parser_list.c parser_handler.c
SRCS_UTILS			=	ft_utils1.c
DIR_MINISHELL		=	$(addprefix ./src/, $(SRCS_MINISHELL)) 
DIR_TOKEN			=	$(addprefix ./src/token/, $(SRCS_TOKEN))
DIR_UTILS			=	$(addprefix ./src/utils/, $(SRCS_UTILS))
DIR_PARSER			=	$(addprefix ./src/parser/, $(SRCS_PARSER))
OBJS				= 	$(DIR_MINISHELL:.c=.o) $(DIR_TOKEN:.c=.o) $(DIR_UTILS:.c=.o) $(DIR_PARSER:.c=.o)

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