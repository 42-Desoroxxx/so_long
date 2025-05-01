##############################################################################################
#                                                                                            #
#   /$$$$$$                                      /$$      /$$           /$$                  #
#  /$$__  $$                                    | $$$    /$$$          | $$                  #
# | $$  \__/  /$$$$$$  /$$$$$$$$ /$$   /$$      | $$$$  /$$$$  /$$$$$$ | $$   /$$  /$$$$$$   #
# | $$       /$$__  $$|____ /$$/| $$  | $$      | $$ $$/$$ $$ |____  $$| $$  /$$/ /$$__  $$  #
# | $$      | $$  \ $$   /$$$$/ | $$  | $$      | $$  $$$| $$  /$$$$$$$| $$$$$$/ | $$$$$$$$  #
# | $$    $$| $$  | $$  /$$__/  | $$  | $$      | $$\  $ | $$ /$$__  $$| $$_  $$ | $$_____/  #
# |  $$$$$$/|  $$$$$$/ /$$$$$$$$|  $$$$$$$      | $$ \/  | $$|  $$$$$$$| $$ \  $$|  $$$$$$$  #
#  \______/  \______/ |________/ \____  $$      |__/     |__/ \_______/|__/  \__/ \_______/  #
#                                /$$  | $$                                                   #
#        )))                    |  $$$$$$/                                    Version 1.0    #
#       (((                      \______/                                                    #
#     +-----+                                   __..--''``---....___   _..._    __           #
#     |     |]      /    //    // //  /// //_.-'    .-/";  `        ``<._  ``.''_ `. / // /  #
#     `-----'   //  //  ///  ///     ///_.-' _..--.'_    \                    `( ) ) // //   #
#         /   / // / ///  /      /// / (_..-' // (< _     ;_..__               ; `' / ///    #
#     ///  //  /  /       // ///  /   / // // //  `-._,_)' // / ``--...____..-' /// / //     #
#    / // / /// //  /// / / // //   //  /// //  /  ///  //  // /// / /  ///   /   / ///  //  #
##############################################################################################

.PHONY: all clean fclean re bonus debug

NAME = so_long
MODE ?= release

# Colors
GREEN = \033[1;32m
BLUE = \033[1;34m
RED = \033[1;31m
RESET = \033[0m

# Compiler
CC = cc
RELEASE_FLAGS = -Wall -Wextra -Werror -O3 -ffast-math -march=native -flto
DEBUG_FLAGS = -Wall -Wextra -O0 -fno-builtin -g
ifeq ($(MODE),debug)
    CFLAGS = $(DEBUG_FLAGS)
    LIB_TARGET = debug
else
    CFLAGS = $(RELEASE_FLAGS)
    LIB_TARGET = all
endif


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
	@echo "$(BLUE)Building libraries in $(MODE) mode...$(RESET)"
	@$(MAKE) --no-print-directory -C libft $(LIB_TARGET)
	@$(MAKE) --no-print-directory -C MacroLibX $(LIB_TARGET)

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
	@$(MAKE) --no-print-directory MODE=debug
