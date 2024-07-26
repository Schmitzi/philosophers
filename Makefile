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

# Name of the program
NAME	=	philo

# Compiler
CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -pthread -g
RM		=	rm -f
MAKEFLAGS += --no-print-directory

# Colours
RED		=	\e[0;91m
GREEN	=	\e[0;92m
YELLOW	=	\e[0;33m
RESET	=	\e[0m

# Files
FILES	=	args \
            free \
			init \
			itoa \
			libft \
			main \
			msg \
			mutex \
			routine \
			thread \
			time \
			utils

# Directories
SRC_DIR	=	./
SRC 	= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))

# Objects
OBJ_DIR	= 	obj/
OBJ		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

# **************************************************************************** #

# Rules

#Target
all:	$(NAME)

# Compile .c to .o
$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $<

# Create obj directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Link .o to executable
$(NAME):	$(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

# Clean up
clean:
	@echo "$(RED)Cleaning...$(RESET)"
	@$(RM) $(OBJ)
	@$(RM) -r $(OBJ_DIR)

# Clean up everything
fclean:		clean
	@$(RM) $(NAME)
	@$(RM) -r $(OBJ_DIR)
	@echo "$(RED)All files cleaned$(RESET)"

# Clean up and recompile
re:		fclean $(OBJ)
	clear ;
	@if [ -n "$(shell $(CC) -MM $(SRC))" ]; then \
		echo "$(YELLOW)Recompiling...$(RESET)"; \
		make all > /dev/null; \
        echo "$(GREEN)Philosophers is ready$(RESET)"; \
	fi

.PHONY:		all clean fclean re
