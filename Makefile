NAME = parsing

LIBFT = ./libft/libft.a

FLAGS = -Wall -Wextra -Werror

SRCS = main.c parsing.c read_map.c parsing_utils.c parse_line.c parse_color.c map_checker.c

OBJS = $(SRCS:.c=.o)

HEADER = parsing.h

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	gcc $(FLAGS) $(OBJS) -lft -Llibft -o $(NAME)

$(LIBFT) :
	@$(MAKE) -C ./libft

%.o : %.c $(HEADER)
	gcc $(FLAGS) -c $<

clean:
	@rm -f $(OBJS)
	@make clean -C ./libft

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)

re : fclean all