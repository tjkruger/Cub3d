# === Project Name ===
NAME        = Cub3d

# === Directories ===
SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = include
LIBFT_DIR   = libft

# === Source groups ===
MAIN        = main.c
BSP			= bsp/bsp.c


# Combine all source groups
SRC         = $(MAIN) $(BSP)

# === Object list (preserve directories) ===
OBJ         = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

# === Compiler flags ===
CC          = cc 
CFLAGS = -g -I$(INC_DIR)

# === Default target ===
all: $(NAME)

# === Build Cub3d ===
$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT_DIR)        # build libft.a
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_DIR)/libft.a $(READLINE) -o $(NAME)
	@echo "$(NAME) built successfully!"

# === Pattern rule for all .c files ===
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# === Ensure object folder exists ===
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

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
	@echo "Full clean done."

re: fclean all

.PHONY: all clean fclean re run
