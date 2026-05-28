# === Project Name ===
NAME        = Cub3d

# === Directories ===
SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = include
LIBFT_DIR   = libft
MLX_DIR     = MLX42

# === Source groups ===
MAIN        = main.c
EXEC_PART   = execution_part/casting.c \
              execution_part/free.c \
              execution_part/game.c \
              execution_part/game_helper.c \
              execution_part/init_player.c \
              execution_part/textures.c
COPILOT     = copilot_code/parse.c \
              copilot_code/helpers.c \
              copilot_code/error.c

VAL			=	val_ini/file_validation.c \
				val_ini/initialisation.c \
				val_ini/check_map.c \
				val_ini/file_parsing.c 
GNL         =	../GNL/get_next_line.c \
                ../GNL/get_next_line_utils.c
#BSP         = bsp/bsp.c

# Combine all source groups
SRC         = $(MAIN) $(EXEC_PART) $(COPILOT)
SRC         = $(MAIN) $(VAL) $(GNL)

# === Object list (preserve directories) ===
OBJ         = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

# === Compiler flags ===
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -I$(INC_DIR) -I$(MLX_DIR)/include

# === Libraries ===
LDFLAGS     = -L$(LIBFT_DIR) -lft \
              -L$(MLX_DIR)/build -lmlx42 \
              -lm -ldl -lpthread -lglfw
#               -framework Cocoa \
#               -framework OpenGL \
#               -framework IOKit

# === Default target ===
all: $(NAME)

# === Build Cub3d ===
$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT_DIR)
	cmake -S $(MLX_DIR) -B $(MLX_DIR)/build --log-level=ERROR
	cmake --build $(MLX_DIR)/build -j4
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "$(NAME) built successfully!"

# === Pattern rule for src .c files ===
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# === Pattern rule for GNL .c files ===
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# === Ensure object folder exists ===
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# === Clean ===
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR)
	@rm -rf GNL/get_next_line.o
	@rm -rf GNL/get_next_line_utils.o
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "Objects cleaned."

# === Full clean ===
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	@echo "Everything cleaned."
	@rm -f $(NAME)
	@rm -rf GNL/get_next_line.o
	@rm -rf GNL/get_next_line_utils.o
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -rf $(MLX_DIR)/build
	@echo "Full clean done."

# === Rebuild ===
re: fclean all

# === Phony targets ===
.PHONY: all clean fclean re
