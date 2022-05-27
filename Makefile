NAME		=	minishell

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -lreadline -g -fsanitize=address

LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a
LIBFLAGS	=	-L $(LIBFT_DIR) -lft -lreadline

PRINTF_DIR	=	ft_printf
PRINTF		=	ft_printf/libftprintf.a

INC			=	-I inc
RM			=	rm -fr

BUILTINS	=	cd.c echo.c env.c exit.c export.c export_utils.c pwd.c unset.c
CORE		=	clear_data.c init_data.c minishell.c signals.c main.c
EXEC		=	execute_one_cmd.c executor.c here_document.c pipes_fds_handling.c \
				processes_handler.c redirects.c sorting.c
EXPAND		=	expand_variables.c expand_utils.c
LEX			=	lexer.c mask_dollar.c mask_n_unmask_chars.c \
				pull_redirects.c treat_quotes.c treat_spaces.c
PARSE		=	parse_vars.c parser.c
TOOLS		=	list_tools_one.c list_tools_two.c str_tools_one.c str_tools_two.c
PROMPT		=	history.c prompt_take_input.c

SRCS_DIR	=	src

FILES		=	$(addprefix BUILTINS/, $(BUILTINS)) \
				$(addprefix EXPAND/, $(EXPAND)) \
				$(addprefix PROMPT/, $(PROMPT)) \
				$(addprefix PARSE/, $(PARSE)) \
				$(addprefix TOOLS/, $(TOOLS)) \
				$(addprefix CORE/, $(CORE)) \
				$(addprefix EXEC/, $(EXEC)) \
				$(addprefix LEX/, $(LEX)) \

SOURCE			=	$(addprefix src/, $(FILES))

OBJS_DIR	=	obj
OBJS		=	$(subst $(SRCS_DIR),$(OBJS_DIR),$(SOURCE:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	make -C $(PRINTF_DIR)
	@-$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) $(LIBFLAGS) -o $@
	@echo ""
	@echo "|		minishell created		|"
	@echo ""

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
		@mkdir -p obj
		@mkdir -p obj/BUILTINS
		@mkdir -p obj/CORE
		@mkdir -p obj/EXEC
		@mkdir -p obj/EXPAND
		@mkdir -p obj/LEX
		@mkdir -p obj/PARSE
		@mkdir -p obj/PROMPT
		@mkdir -p obj/TOOLS
		$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) fclean
	make -C $(PRINTF_DIR) fclean
	@echo ""
	@echo "|		minishell deleted		|"
	@echo ""

fclean: clean
	$(RM) obj
	$(RM) $(NAME)

install:
	@sudo apt-get -y install libreadline-dev

re: fclean all

git:
	git add .
	git status
	git commit -m "$m"

.PHONY:		all clean fclean re git
