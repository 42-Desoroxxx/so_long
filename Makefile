# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llage <llage@student.42angouleme.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 22:55:02 by llage             #+#    #+#              #
#    Updated: 2025/04/30 19:22:13 by llage            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re bonus slow

GREEN = \033[1;32m
BLUE = \033[1;34m
RED = \033[1;31m
RESET = \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -ffast-math -march=native -flto
NAME = so_long
DEPS = includes
SRC = src
OBJ = obj

SRC_FILES := so_long.c
SRCS := $(addprefix $(SRC)/,$(SRC_FILES))
OBJS := $(patsubst $(SRC)/%,$(OBJ)/%,$(SRCS:.c=.o))

all: $(NAME)

libft/libft.a:
	@$(MAKE) -s -C libft

MacroLibX/libmlx.so:
	@$(MAKE) -s -C MacroLibX

$(OBJ)/%.o: $(SRC)/%.c $(DEPS)
	@mkdir -p $(@D)
	@echo "$(BLUE)Compiling$(RESET) $<..."
	@$(CC) $(CFLAGS) -I$(DEPS) -Ilibft/includes -IMacroLibX/includes -c $< -o $@

$(NAME): $(OBJS) libft/libft.a MacroLibX/libmlx.so
	@echo "$(GREEN)Linking$(RESET) $@..."
	@$(CC) $(CFLAGS) $^ -o $@ -lSDL2
	@echo "$(GREEN)Done!$(RESET)"

clean:
	@echo "$(RED)Cleaning$(RESET) object files..."
	@rm -rf $(OBJ)
	@$(MAKE) -s -C libft clean

fclean: clean
	@echo "$(RED)Removing$(RESET) $(NAME)..."
	@rm -f $(NAME)
	@$(MAKE) -s -C libft fclean

re: fclean
	@$(MAKE) --no-print-directory all

bonus: all

slow:
	@echo "$(RED)Compiling in slow mode$(RESET) slowly but steady I get it..."
	@$(MAKE) --no-print-directory all CFLAGS="$(CFLAGS) -O0 -fno-builtin -g"

