NAME = cub3d

CFLAGS = -Wall -Wextra -Werror -Imlx

SRC = cub3D.c ./keys_cordinations/cordinations.c ./keys_cordinations/key_press_release.c ./keys_cordinations/player_first_cordinations.c \
		./tmp/ft_split.c ./tmp/get_map.c ./tmp/ft_strlen.c ./texturse_reader/get_texturse_buff.c ./texturse_reader/get_texturse_buff_utils.c \
		./draw/draw.c \

OBJ = $(SRC:.c=.o)

%.o: %.c cub3D.h
	@$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ) cub3D.h
	@$(CC) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

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
