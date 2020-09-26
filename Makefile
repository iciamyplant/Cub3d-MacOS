SRC =	minimap.c \
		parsing.c \
		parsing_color_resolution_texture.c \
		parsing_map.c \
		parsing_utils.c \
		keys_draw.c \
		raycasting_init.c \
		raycasting_utils.c \
		hitpoints.c \
		raycasting_move.c \
		raycasting.c \
		sprites.c

NAME = Cub3D

LIBFT_DIR = libft
LIBFT = libft.a
MLX_DIR = mlx
MLX = libmlx.dylib

# diff entre .a et .dylib
# .a = lib static, les fonctions utilisees sont directement ecrite dans le binaire
# .dylib = lib dynamique, les fonctions doivent etre chargees au momnent ou on lance le binaire

CFLAGS = -Wall -Wextra -Werror -MMD -O3

OBJ_DIR = obj
SRC_DIR = src
INC_DIR = inc

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
DPD = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.d))

# -C faire make comme si on etait dana le dossier
# -j multisreder / ameliore la vitesse de compliation
# Pas de regle opti car makefile mlx pas compatible
all:
	@$(MAKE) -C $(MLX_DIR)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -j $(NAME)

# permet de pouvoir comparer la derniere modification de la dep par rapport a la regle
# -L donner le nom du dossier / -l donner le nom le la lib
# loader path = ecrit le chemin de la mlx dans le binaire pour pouvoir la retrouver au moment ou on lance le binaire
$(NAME): $(OBJ)
		@gcc $(CFLAGS) -o $(NAME) $(OBJ) -L $(MLX_DIR) -l mlx -L $(LIBFT_DIR) -l ft
		@install_name_tool -change $(MLX) @loader_path/$(MLX_DIR)/$(MLX) $(NAME)
		@echo $(NAME) : Created !

# si le .c est plus recent que le .o on rentre dans la regle
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(MLX_DIR)/$(MLX) $(LIBFT_DIR)/$(LIBFT) | .gitignore
		@mkdir -p $(OBJ_DIR)
		@gcc $(CFLAGS) -I $(INC_DIR) -I $(MLX_DIR) -I $(LIBFT_DIR) -c $< -o $@

.gitignore:
		@echo $(NAME) > .gitignore

clean:
	@$(MAKE) clean -C $(MLX_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "obj deleted"

fclean:	clean
	@rm -rf $(LIBFT_DIR)/$(LIBFT)
	@echo "[$(LIBFT)]: deleted"
	@rm -rf $(NAME)
	@echo "[$(NAME)]: deleted"

re: fclean all

.PHONY: all, clean, fclean, re

# Utilise les .d (et ignore s'ils n'existe pas)
-include $(DPD)
