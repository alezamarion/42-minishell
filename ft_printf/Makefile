NAME		=	libftprintf.a
FLAGS		=	-Wall -Wextra #-Werror -g3 -O3
#CC			= 	clang
RM			=	rm -fr
MK			=	make -C
LIBPATH		=	../libft
LIB			=	../libft/libft.a
AR			=	ar rsc

SRC			=	src/ft_printf.c \
				src/is_valid.c \
				src/nbr_conversion.c \
				src/print_args.c \
				src/printflags.c \
				src/utils.c \
				specifiers/specifier_c.c \
				specifiers/specifier_d_or_i.c \
				specifiers/specifier_p.c \
				specifiers/specifier_s.c \
				specifiers/specifier_u.c \
				specifiers/specifier_x_or_upper_x.c \

OBJ			=	$(addprefix obj/, $(notdir $(SRC:.c=.o)))

all:		$(NAME)

$(NAME):	$(LIB)
	@$(CC) $(FLAGS) -I ./inc -c $(SRC)
	@mkdir -p obj
	@mv $(notdir $(SRC:.c=.o)) obj
	@$(AR) $(NAME) $(OBJ)
	@echo "Printf is ready! [ OK ]"

$(LIB):
	@echo "Compiling Libft [ .. ]"
	@$(MK) $(LIBPATH)
	@echo "Libft is ready! [ OK ]"
	@cp libft/libft.a libftprintf.a

clean:
	@$(RM) ./obj
	@$(MK) $(LIBPATH) clean
	@echo "Object files removed."

fclean:		clean
	@$(RM) $(NAME)
	@$(MK) $(LIBPATH) fclean
	@echo "Binaries removed."

bonus:		all

re:			fclean all

.PHONY: all, clean, fclean, re, bonus
