# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/22 14:29:42 by mgeiger-          #+#    #+#              #
#    Updated: 2024/06/23 14:39:59 by mgeiger-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -pthread -g
RM		=	rm -f

RED		=	\e[0;91m
BLUE	=	\e[0;94m
GREEN	=	\e[0;92m
YELLOW	=	\e[0;33m
WHITE	=	\e[0;97m
BOLD	=	\e[1m
U_LINE	=	\e[4m
RESET	=	\e[0m

FILES	=	args \
            error \
			init \
			main \
			mutex \
			routine \
			thread \
			time \
			utils

SRC_DIR = 	./
SRC 	= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))

OBJ_DIR	= 	obj/
OBJ		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

$(OBJ_DIR)%.o: %.c $(wildcard *.h)
	@mkdir -p obj
	@$(CC) $(CFLAGS) -c -o $@ $<

all:	$(NAME)

$(NAME): $(OBJ)
	@echo "$(YELLOW)Compiling philosophers$(RESET)"
	@$(CC) $(OBJ) $(CFLAGS) -o $(NAME)
	@echo "$(GREEN)Philosophers built$(RESET)"

clean:
	@$(RM) $(OBJ)
	@if [ -d "obj" ]; then \
		rm -r obj/; \
	fi
	@echo "$(RED)Removed objects$(RESET)"

fclean:	clean
	@$(RM) $(NAME)
	@echo "$(RED)All files cleaned$(RESET)"

re:		fclean all
	clear ;
	@echo "$(GREEN)Files cleaned and program re-compiled$(RESET)"

.PHONY:		all clean fclean re philo
