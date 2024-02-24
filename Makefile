# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 16:20:41 by zlaarous          #+#    #+#              #
#    Updated: 2024/02/06 17:06:42 by aouhbi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_M	= cub3d
NAME_B	= cub3d_bonus
CFLAGS	= -Wextra -Wall -Werror -O2 #-g -fsanitize=undefined,signed-integer-overflow,unsigned-integer-overflow  #-b -g3 #-Wunreach0able-code -Ofast
# CFLAGS	= -Wextra -Wall -Werror -g -fsanitize=address
LIBMLX	= ./MLX42

HEADER_B = Bonus/include/cub3d.h
HEADER_M = Mandatory/include/cub3d.h

HEADERS	= -I ./include -I $(LIBMLX)/include
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS_M	= 	Mandatory/main.c \
			Mandatory/execution_part/render_loop.c \
			Mandatory/execution_part/hook.c \
			Mandatory/execution_part/init.c \
			Mandatory/execution_part/my_mlx_setup.c \
			Mandatory/execution_part/render_player.c \
			Mandatory/execution_part/rays.c \
			Mandatory/execution_part/intersaction.c \
			Mandatory/execution_part/distance.c \
			Mandatory/execution_part/render3dProjection.c \
			Mandatory/execution_part/minimap_setup.c \
			Mandatory/parcing/parcing.c \
			Mandatory/parcing/map_parcing.c \
			Mandatory/parcing/get_next_line.c \
			Mandatory/parcing/get_next_line_utils.c \
			Mandatory/parcing/tools.c \
			Mandatory/parcing/tools2.c \
			Mandatory/parcing/tools3.c \
			Mandatory/parcing/n_e_w_s_check.c \
			Mandatory/parcing/f_c_check.c \
			Mandatory/parcing/utils.c \
			Mandatory/parcing/map_utils.c \
			Mandatory/parcing/garbage_collector.c

SRCS_B	= 	Bonus/main.c \
			Bonus/execution_part/render_loop.c \
			Bonus/execution_part/hook.c \
			Bonus/execution_part/init.c \
			Bonus/execution_part/my_mlx_setup.c \
			Bonus/execution_part/render_player.c \
			Bonus/execution_part/rays.c \
			Bonus/execution_part/intersaction.c \
			Bonus/execution_part/distance.c \
			Bonus/execution_part/render3dProjection.c \
			Bonus/execution_part/minimap_setup.c \
			Bonus/parcing/parcing.c \
			Bonus/parcing/map_parcing.c \
			Bonus/parcing/get_next_line.c \
			Bonus/parcing/get_next_line_utils.c \
			Bonus/parcing/tools.c \
			Bonus/parcing/tools2.c \
			Bonus/parcing/tools3.c \
			Bonus/parcing/n_e_w_s_check.c \
			Bonus/parcing/f_c_check.c \
			Bonus/parcing/utils.c \
			Bonus/parcing/map_utils.c \
			Bonus/parcing/garbage_collector.c


OBJS_M	= ${SRCS_M:.c=.o}
OBJS_B	= ${SRCS_B:.c=.o}

all: libmlx $(NAME_M)

%.o: %.c ${HEADER_B} ${HEADER_M}
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

bonus : libmlx ${OBJS_B}
	@$(CC) $(OBJS_B) $(MLX) $(CFLAGS) $(HEADERS) -o $(NAME_B)

MLX = ./MLX42/build/libmlx42.a $(CFLAGS) -Iinclude -lglfw -L'/Users/aouhbi/.brew/Cellar/glfw/3.3.9/lib' -framework Cocoa -framework OpenGL -framework IOKit

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4


$(NAME_M): $(OBJS_M)
	@$(CC) $(OBJS_M) $(MLX) $(CFLAGS) $(HEADERS) -o $(NAME_M)

clean:
	@rm -rf $(OBJS_M)
	@rm -rf $(LIBMLX)/build

clean_bonus:
	@rm -rf $(OBJS_B)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME_M)

fclean_bonus: clean_bonus
	@rm -rf ${NAME_B}

re: fclean all

re_bonus: fclean_bonus bonus

.PHONY: all, clean, fclean, re, bonus, clean_bonus, fclean, re_bonus, libmlx