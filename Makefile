SRC = parcing.c get_next_line.c get_next_line_utils.c ft_split.c map_parcing.c

OBJ = ${SRC:%.c=%.o}

HEAD = parcing.h get_next_line.h

NAME = cub3d

CFLG = cc -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJ} ${HEAD}
	${CFLG} ${OBJ} -o ${NAME}

%.o: %.c
	${CFLG} -c $< -o $@

clean:
	rm -rf ${OBJ}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re