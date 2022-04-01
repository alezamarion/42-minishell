NAME		=	minishell
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -lreadline -g #-fsanitize=address
LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a
LIBFLAGS	=	-L $(LIBFT_DIR) -lft
VPATH 		= 	src src/CORE src/PROMPT src/LEX \
				src/PARSE src/EXPAND src/EXEC \
				src/BUILTINS src/TOOLS
RM			=	rm -fr
HEADERS		=	minishell.h

SRC_FILES	=	main.c \
				hello.c \
				data_handler.c \
				minishell.c \
				prompt_take_input.c \
				handle_quotes.c \
				history.c \
				lexer.c \
				parser.c \
				expand_variables.c \
				sorting.c \
				executor.c \
				exit.c \
				help.c \
				echo.c \
				str_tools.c \
				list_tools.c \
				parse_vars.c

OBJ			=	$(SRC_FILES:%.c=%.o)
OBJ_DIR		=	obj

$(OBJ_DIR)/%.o: %.c $(HEADERS)
		$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES) 

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBFT) $(OBJ)
	mv $(OBJ) $(OBJ_DIR)
	$(CC) $(addprefix obj/, $(OBJ)) $(CFLAGS) $(LIBFLAGS) -o $@
	@echo ""
	@echo "|		minishell created		|"
	@echo ""

$(LIBFT):
		make -C $(LIBFT_DIR)

$(OBJ_DIR):
		mkdir -p $(OBJ_DIR)

clean:
	make -C $(LIBFT_DIR) fclean
	@echo ""
	@echo "|		minishell deleted		|"
	@echo ""

fclean: clean
	$(RM) $(OBJ_DIR)
	$(RM) $(NAME)

install:
	@sudo apt-get -y install libreadline-dev

re: fclean all

git:
	git add .
	git status
	git commit -m "$m"

.PHONY:		all clean fclean re git