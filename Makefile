NAME := fdf
INCLUDE = include
LIBFT = libft
CC := cc
CFLAGS := -Wall -Wextra -Werror -g -Lmlx_linux -lmlx_Linux \
          -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
SRCS := fdf.c fdf_draw.c fdf_init_end.c fdf_blocks.c\
        fdf_utils.c fdf_display.c fdf_draw_utils.c fdf_scale.c\

OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	@make -C $(LIBFT)
	$(CC) $(OBJS) $(CFLAGS) -Ilibft/ -Llibft/ -lft -o $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -g -c $< -o $@

clean:
	@make clean -C $(LIBFT)
	rm -rf $(OBJS)

fclean: clean
	rm -rf fdf
	rm -rf libft/libft.a

re: fclean all

.PHONY: all clean fclean re
