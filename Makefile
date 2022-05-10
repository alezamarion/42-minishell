NAME		=	minishell
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -lreadline -g -fsanitize=address 
LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a
LIBFLAGS	=	-L $(LIBFT_DIR) -lft
PRINTF_DIR	=	ft_printf
PRINTF		=	ft_printf/libftprintf.a
VPATH 		= 	src src/CORE src/PROMPT src/LEX \
				src/PARSE src/EXPAND src/EXEC \
				src/BUILTINS src/TOOLS
RM			=	rm -fr
HEADERS		=	minishell.h

SRC_FILES	=	main.c \
				minishell.c \
				hello.c \
				clear_data.c \
				init_data.c \
				prompt_take_input.c \
				history.c \
				lexer.c \
				pull_redirects.c \
				parser.c \
				redirects.c \
				expand_variables.c \
				sorting.c \
				executor.c \
				exit.c \
				help.c \
				echo.c \
				env.c \
				export.c \
				unset.c \
				str_tools.c \
				here_document.c \
				execute_one_cmd.c \
				mask_n_unmask_chars.c \
				cd.c \
				pwd.c \
				list_tools.c \
				parse_vars.c \
				treat_quotes.c \
				mask_dollar.c \
				pipes_fds_handling.c \
				processes_handler.c \
				signals.c

OBJ			=	$(SRC_FILES:%.c=%.o)
OBJ_DIR		=	obj

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBFT) $(OBJ)
	mv $(OBJ) $(OBJ_DIR)
	$(CC) $(addprefix obj/, $(OBJ)) $(LIBFT) $(PRINTF) $(CFLAGS) $(LIBFLAGS) -fPIE -o $@
	@echo ""
	@echo "|		minishell created		|"
	@echo ""

$(LIBFT):
		make -C $(LIBFT_DIR)
		make -C $(PRINTF_DIR)

$(OBJ_DIR):
		mkdir -p $(OBJ_DIR)

clean:
	make -C $(LIBFT_DIR) fclean
	make -C $(PRINTF_DIR) fclean
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
