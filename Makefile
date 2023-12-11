# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/12 17:42:16 by asuc              #+#    #+#              #
#    Updated: 2023/12/12 00:44:31 by asuc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BGreen		=	$(shell echo "\033[1;32m")
RESET		=	$(shell echo "\033[0m")
BRed		=	$(shell echo "\033[1;31m")
NAME		=	fractol
COMP		=	clang
CFLAGS		=	-Wall -Werror -Wextra
libft		=	Libft/
SRC			=	main.c
MacroLibX	=	MacroLibX/

OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o : %.c
	@$(COMP) -gdwarf-4 -fPIE -O3 -march=native $(CFLAGS) -o $@ -c $<

$(NAME) : $(OBJ)
	@make --no-print-directory -C $(libft)
	@make --no-print-directory -C $(MacroLibX)
	@cp $(libft)libft.a libft.a
	@clang -gdwarf-4 -fPIE $(CFLAGS) -o $(NAME) $(OBJ) libft.a MacroLibX/libmlx.so -lSDL2
	@echo "$(BGreen)Compilation OK$(RESET)"

clean :
	@make clean --no-print-directory -C $(libft)
	@make clean --no-print-directory -C $(MacroLibX)
	@rm -f $(OBJ)
	@echo "$(BRed)Erase all .o files$(RESET)"

fclean : clean
	@make fclean --no-print-directory -C $(libft)
	@make fclean --no-print-directory -C $(MacroLibX)
	@rm -f $(NAME) libft.a
	@echo "$(BRed)Erase $(NAME), libft.a and $(MacroLibX)$(RESET)"

test : all
	@./$(NAME)

valrindTest : all
	@valgrind --suppressions=test.supp --leak-check=full --show-reachable=yes --error-limit=no ./$(NAME)
re : fclean all

.PHONY: all fclean clean re


