.PHONY: all clean fclean re bonus

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

SRC_FILES := so_long
SRCS := $(addprefix $(SRC)/,$(SRC_FILES))
OBJS := $(patsubst $(SRC)/%,$(OBJ)/%,$(SRCS:.c=.o))

all: $(NAME)

libft/libft.a:
	@$(MAKE) -s -C libft

$(OBJ)/%.o: $(SRC)/%.c $(DEPS)
	@mkdir -p $(@D)
	@echo "$(BLUE)Compiling$(RESET) $<..."
	@$(CC) $(CFLAGS) -I$(DEPS) -Ilibft/includes -c $< -o $@

$(NAME): $(OBJS) libft/libft.a
	@echo "$(GREEN)Linking$(RESET) $@..."
	@$(CC) $(CFLAGS) $^ -o $@
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
