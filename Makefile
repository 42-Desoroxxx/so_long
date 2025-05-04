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

.PHONY: all debug clean fclean re re_debug bonus

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

# Libraries
LIB_DIRS = libft MacroLibX
LIB_FILES = libft/libft.a MacroLibX/libmlx.so
LDFLAGS = -lSDL2

# Directories
SRC = src
OBJ = obj
INCLUDES = -Iincludes $(foreach lib,$(LIB_DIRS),-I$(lib)/includes) $(shell sdl2-config --cflags)

# Sources
SRC_FILES := so_long.c hooks.c
SRCS := $(addprefix $(SRC)/,$(SRC_FILES))
OBJS := $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))

all: $(NAME)

debug:
	@echo "$(GREEN)Building in debug mode$(RESET)"
	@$(MAKE) --no-print-directory MODE=debug

$(OBJ):
	@mkdir -p $@ $(dir $(OBJS))

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	@echo "$(BLUE)Compiling$(RESET) $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

libs:
	@echo "$(BLUE)Building libraries in $(MODE) mode...$(RESET)"
	@for lib in $(LIB_DIRS); do \
		$(MAKE) --no-print-directory -C $$lib $(LIB_TARGET); \
	done

$(NAME): $(OBJS) | libs
	@echo "$(GREEN)Linking$(RESET) $@..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIB_FILES) -o $@ $(LDFLAGS)
	@echo "$(GREEN)Successfully compiled $(NAME)!$(RESET)"

clean:
	@echo "$(RED)Cleaning$(RESET) $(NAME)'s object files..."
	@rm -rf $(OBJ)
	@for lib in $(LIB_DIRS); do \
		$(MAKE) --no-print-directory -s -C $$lib clean; \
	done

fclean: clean
	@echo "$(RED)Removing$(RESET) $(NAME)..."
	@rm -f $(NAME)
	@for lib in $(LIB_DIRS); do \
		$(MAKE) --no-print-directory -s -C $$lib fclean; \
	done

re: fclean all

re_debug: fclean debug

bonus: all
