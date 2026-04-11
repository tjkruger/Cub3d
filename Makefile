# === Project Name ===
NAME        = Cub3d

# === Directories ===
SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = include
LIBFT_DIR   = libft
MLX_DIR     = MLX42

# === Source groups ===
MAIN        =	main.c
VAL			=	val_ini/file_validation.c
				val_ini/initialisation.c
#BSP         = bsp/bsp.c

# Combine all source groups
SRC         = $(MAIN) #$(BSP)

# === Object list (preserve directories) ===
OBJ         = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

# === Compiler flags ===
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -I$(INC_DIR) -I$(MLX_DIR)/include

# === Libraries ===
LDFLAGS     = -L$(LIBFT_DIR) -lft \
              -L$(MLX_DIR)/build -lmlx42 \
              -lglfw \
              -lm \
              -lXext -lX11 \
              -ldl -lpthread

# === Default target ===
all: $(NAME)

# === Build Cub3d ===
$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT_DIR)
	cmake -S $(MLX_DIR) -B $(MLX_DIR)/build --log-level=ERROR
	cmake --build $(MLX_DIR)/build -j4
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "$(NAME) built successfully!"

# === Pattern rule for all .c files ===
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# === Ensure object folder exists ===
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# === Bonus ===
bonus: all

# === Run ===
run: $(NAME)
	./$(NAME)

# === Clean ===
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "Objects cleaned."

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -rf $(MLX_DIR)/build
	@echo "Full clean done."

re: fclean all

.PHONY: all clean fclean re run bonus