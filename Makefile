# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/12 17:42:16 by asuc              #+#    #+#              #
#    Updated: 2023/12/14 17:29:34 by asuc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BGreen		=	$(shell echo "\033[1;32m")
RESET		=	$(shell echo "\033[0m")
BRed		=	$(shell echo "\033[1;31m")
BCyan		=	$(shell echo "\033[1;36m")
Green		=	$(shell echo "\033[0;32m")
NAME		=	fract-ol
COMP		=	clang
CFLAGS		=	-Wall -Werror -Wextra
libft		=	Libft/
SRC			=	srcs/color.c \
				srcs/fractol.c \
				srcs/hook_key.c \
				srcs/iter_change.c \
				srcs/mandelbrot.c \
				srcs/moves.c \
				srcs/zoom.c \
				srcs/julia.c \
				srcs/burningship.c \

MacroLibX	=	MacroLibX/

# on ajoute un message jsute avant de faire la compilation de tout les OBJ
OBJ = $(SRC:.c=.o)

TOTAL = $(words $(OBJ))
CURR = 0

define update_progress
  $(eval CURR=$(shell echo $$(($(CURR)+1))))
  @echo -n "\033[1A\033[K"
  @echo -n "$(Green)[`echo "scale=2; $(CURR)/$(TOTAL)*100" | bc`%] Compiling $< \n$(RESET)"
endef

all : $(NAME)

%.o : %.c
	@if [ $(CURR) -eq 0 ]; then \
		echo "\n$(BCyan)Compiling object files for $(NAME)...$(RESET)\n"; \
	fi
	@$(COMP) -gdwarf-4 -fPIE -O3 -march=native $(CFLAGS) -o $@ -c $<
	@$(B)
	@$(call update_progress)

start :
	@echo "$(BCyan)Compilation Start$(NAME)$(RESET)\n\n"

$(NAME) : $(OBJ)
	@make --quiet --no-print-directory -C $(libft)
	@make --quiet --no-print-directory -j -C $(MacroLibX)
	@cp $(libft)libft.a libft.a
	@clang -gdwarf-4 -fPIE $(CFLAGS) -o $(NAME) $(OBJ) libft.a MacroLibX/libmlx.so -lSDL2 -lm
	@echo "\n$(BGreen)Compilation Final $(NAME)$(RESET)"

clean :
	@make clean --quiet --no-print-directory -C $(libft)
	@make clean --quiet --no-print-directory -C $(MacroLibX)
	@rm -f $(OBJ)
	@echo "$(BRed)Erase all .o files$(RESET)"

fclean : clean
	@make fclean --quiet --no-print-directory -C $(libft)
	@make fclean --quiet --no-print-directory -C $(MacroLibX)
	@rm -f $(NAME) libft.a
	@echo "$(BRed)Erase $(NAME), libft.a and $(MacroLibX)$(RESET)"

test : all
	@./$(NAME)

valrindTest : all
	@valgrind --suppressions=test.supp --leak-check=full --show-reachable=yes --error-limit=no ./$(NAME)
re : fclean all

.PHONY: all fclean clean re


