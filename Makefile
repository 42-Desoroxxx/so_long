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

.PHONY: all clean fclean re bonus debug debug_libft debug_mlx

# Colors
GREEN = \033[1;32m
BLUE = \033[1;34m
RED = \033[1;31m
RESET = \033[0m

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -ffast-math -march=native -flto
DEBUG_FLAGS = -Wall -Wextra -O0 -fno-builtin -g
NAME = so_long

# Directories
SRC = src
OBJ = obj
INCLUDES = -Iincludes -Ilibft/includes -IMacroLibX/includes

# Libraries
LIBS = libft/libft.a MacroLibX/libmlx.so
LDFLAGS = -lSDL2

# Source files
SRC_FILES := so_long.c
SRCS := $(addprefix $(SRC)/,$(SRC_FILES))
OBJS := $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))

all: $(NAME)

$(OBJ):
	@mkdir -p $@

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	@echo "$(BLUE)Compiling$(RESET) $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

libft/libft.a:
	@$(MAKE) -s -C libft

MacroLibX/libmlx.so:
	@$(MAKE) -s -C MacroLibX

$(NAME): $(OBJS) $(LIBS)
	@echo "$(GREEN)Linking$(RESET) $@..."
	@$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "$(GREEN)Done!$(RESET)"

clean:
	@echo "$(RED)Cleaning$(RESET) object files..."
	@rm -rf $(OBJ)
	@$(MAKE) -s -C libft clean
	@$(MAKE) -s -C MacroLibX clean

fclean: clean
	@echo "$(RED)Removing$(RESET) $(NAME)..."
	@rm -f $(NAME)
	@$(MAKE) -s -C libft fclean
	@$(MAKE) -s -C MacroLibX fclean

re: fclean all

bonus: all

debug_libft:
	@$(MAKE) -s -C libft debug

debug_mlx:
	@$(MAKE) -s -C MacroLibX debug

debug: CFLAGS = $(DEBUG_FLAGS)
debug: debug_libft debug_mlx
	@echo "$(GREEN)DEBUG$(RESET)"
	@$(MAKE) --no-print-directory all

