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

##############################################################################################
#                                                                                            #
#   /$$$$$$                                      /$$      /$$           /$$                  #
#  /$$__  $$                                    | $$$    /$$$          | $$                  #
# | $$  \__/  /$$$$$$  /$$$$$$$$ /$$   /$$      | $$$$  /$$$$  /$$$$$$ | $$   /$$  /$$$$$$   #
# | $$       /$$__  $$|____ /$$/| $$  | $$      | $$ $$/$$ $$ |____  $$| $$  /$$/ /$$__  $$  #
# | $$      | $$  \ $$   /$$$$/ | $$  | $$      | $$  $$$| $$  /$$$$$$$| $$$$$$/ | $$$$$$$$  #
# | $$    $$| $$  | $$  /$$__/  | $$  | $$      | $$\  $ | $$ /$$__  $$| $$_  $$ | $$_____/  #
# |  $$$$$$/|  $$$$$$/ /$$$$$$$$|  $$$$$$$      | $$ \/  | $$|  $$$$$$$| $$ \  $$|  $$$$$$$  #
#   \______/  \______/ |________/ \____  $$      |__/     |__/ \_______/|__/  \__/ \_______/ #
#                                /$$  | $$                                                   #
#        )))                   |  $$$$$$/                                                    #
#       (((                      \______/                                                    #
#     +-----+                                   __..--''``---....___   _..._    __           #
#     |     |]      /    //    // //  /// //_.-'    .-/";  `        ``<._  ``.''_ `. / // /  #
#     `-----'   //  //  ///  ///     ///_.-' _..--.'_    \                    `( ) ) // //   #
#         /   / // / ///  /      /// / (_..-' // (< _     ;_..__               ; `' / ///    #
#     ///  //  /  /       // ///  /   / // // //  `-._,_)' // / ``--...____..-' /// / //     #
#    / // / /// //  /// / / // //   //  /// //  /  ///  //  // /// / /  ///   /   / ///  //  #
##############################################################################################
.PHONY: all clean fclean re bonus debug libs_debug

NAME = so_long

# Colors
GREEN = \033[1;32m
BLUE = \033[1;34m
RED = \033[1;31m
RESET = \033[0m

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -ffast-math -march=native -flto
DEBUG_FLAGS = -Wall -Wextra -O0 -fno-builtin -g

# Directories
INCLUDES = -Iincludes -Ilibft/includes -IMacroLibX/includes
SRC = src
OBJ = obj

# Libraries
LIBS = libft/libft.a MacroLibX/libmlx.so
LDFLAGS = -lSDL2

# Sources
SRC_FILES := so_long.c
SRCS := $(addprefix $(SRC)/,$(SRC_FILES))
OBJS := $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))

all: $(NAME)

$(OBJ):
	@mkdir -p $@

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	@echo "$(BLUE)Compiling$(RESET) $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

libs:
	@echo "$(BLUE)Building libraries...$(RESET)"
	@$(MAKE) --no-print-directory -C libft
	@$(MAKE) --no-print-directory -C MacroLibX

debug_libs:
	@echo "$(BLUE)Building libraries in debug mode...$(RESET)"
	@$(MAKE) --no-print-directory -C libft debug
	@$(MAKE) --no-print-directory -C MacroLibX debug

$(NAME): $(OBJS) | libs
	@echo "$(GREEN)Linking$(RESET) $@..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@ $(LDFLAGS)
	@echo "$(GREEN)Successfully compiled $(NAME)!$(RESET)"

clean:
	@echo "$(RED)Cleaning$(RESET) $(NAME)'s object files..."
	@rm -rf $(OBJ)
	@$(MAKE) --no-print-directory -s -C libft clean
	@$(MAKE) --no-print-directory -s -C MacroLibX clean

fclean: clean
	@echo "$(RED)Removing$(RESET) $(NAME)..."
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -s -C libft fclean
	@$(MAKE) --no-print-directory -s -C MacroLibX fclean

re: fclean all

bonus: all

debug:
	@echo "$(GREEN)Building in debug mode$(RESET)"
	@$(MAKE) --no-print-directory -s debug_libs
	@$(MAKE) --no-print-directory -s $(NAME) CFLAGS="$(DEBUG_FLAGS)"
