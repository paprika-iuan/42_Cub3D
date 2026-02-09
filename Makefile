NAME	=	cub3d
SRC		=	src/main.c \
			src/parser/parser.c \
			src/parser/parse_info.c \
			src/parser/parse_textures.c \
			src/parser/parse_colors.c \
			src/parser/parse_map.c \
			src/parser/validate_map.c \
			src/render/rend_main.c \
			src/render/rend_move.c \
			src/render/rend_pos.c \
			src/render/rend_3d.c \
			src/render/rend_exit.c \
			src/render/rend_texture.c

LIBFT_DIR = ./lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

LIBMLX	:= ./lib/MLX42

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
DEP = $(SRC:%.c=$(OBJ_DIR)/%.d)

CC = cc
CCFLAGS = -Wall -Wextra -Werror -g -Wunreachable-code -O3 -fsanitize=address

INCLUDES = -I$(LIBFT_DIR) -I$(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm


all: libft libmlx $(NAME)

-include $(DEP)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) $(LIBFT) $(LIBS) -o $(NAME)
	
libft:
	$(MAKE) -C $(LIBFT_DIR)

libmlx:
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJ_DIR)/%.o: %.c | Makefile $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -MMD -MP $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(LIBMLX)/build

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re libft libmlx