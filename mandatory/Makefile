NAME = cub3d

LIBFT = ./libft/libft.a

CFLAGS = -Wall -Wextra -Werror -Imlx

SRC = cub3D.c ./keys_cordinations/cordinations.c ./keys_cordinations/key_press_release.c ./keys_cordinations/player_first_cordinations.c \
		./texturse_reader/get_texturse_buff.c ./texturse_reader/get_texturse_buff_utils.c \
		./draw/draw.c ./minimap/minimap.c ./imgs/creat_imgs.c ./draw/cast_rays.c ./draw/rander_wall.c ./draw/cast_rays_utils1.c ./draw/cast_rays_utils2.c \
		./keys_cordinations/cordinations_utils.c ./parsing/parsing.c ./parsing/read_map.c ./parsing/parsing_utils.c ./parsing/parse_line.c ./parsing/parse_color.c ./parsing/map_checker.c ./parsing/map_checker_utils.c\

OBJ = $(SRC:.c=.o)

%.o: %.c cub3D.h
	@$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ) cub3D.h $(LIBFT)
	@$(CC) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME) -lft -L./parsing/libft

$(LIBFT) :
	@$(MAKE) -C ./parsing/libft

clean :
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

# NAME = cub3d

# CFLAGS = -Wall -Wextra -Werror -Imlx

# SRC = main.c get_map.c ft_split.c ft_strlen.c\
# OBJECT_PATH = ./obj/

# OBJECTS = $(addprefix $(OBJECT_PATH), $(SRC:.c=.o))


# %.o: %.c
# 	@$(CC) $(CFLAGS) -c $< -o $@

# all : $(NAME)

# $(NAME) : $(OBJ) cub3D.h
# 	@$(CC) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

# $(OBJECT_PATH)%.o  : %.c
# 	$(CC)  $(CFLAGS) -o $@  -c $^

# clean :
# 	@rm -rf $(OBJ)

# fclean : clean
# 	@rm -rf $(NAME)

# re : fclean all