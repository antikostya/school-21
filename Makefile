# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/25 12:07:16 by tlucanti          #+#    #+#              #
#    Updated: 2021/04/20 15:33:50 by tlucanti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
NAME	=	miniRT
CFLAGS	=	-Wall -Wextra -Werror
INCLUDE =	-I ../GUIlib/include
COPTIONS=	-O3
DEPS	=	ray_traycer.h objects.h
RM		=	rm -f
AR		=	ar rcs
LIBRARY	=	-L ../GUIlib -lm `../GUIlib/guiflags.sh`
SRCS	=	\
	camera              circle          clean_scene_1       clean_scene_2       \
	color_1             color_2         compute_lightning   cylinder            \
	keyboard_manager    key_switcher    light               main                \
	math_utils          matrix          multiassignment     plane               \
	point_1             point_2         point_3             scene_parcer_1      \
	scene_parcer_2      scene_parcer_3  scene_parcer_4      screenshot          \
	sphere              square          ternary             trace_ray           \
	triangle            utils_1         utils_2             utils_3             \
	\
	get_next_line/get_next_line         get_next_line/get_next_line_utils

OBJS	=	${SRCS:=.o}
OBJS_BONUS=	${SRCS_BONUS:=.o}
LIBFT	=	./libft/libft.a

all: $(NAME)

.c.o:
	${CC} ${CFLAGS} ${COPTIONS} ${INCLUDE} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	${MAKE} -C libft
	${CC} -o ${NAME} ${CFLAGS} ${COPTIONS} ${OBJS} ${LIBRARY} ${LIBFT}

clean:
	${MAKE} -C libft clean
	${RM} ${OBJS}
	${RM} ${OBJS_BONUS}
	${RM} get_next_line.o get_next_line_utils.o test.o

fclean: clean
	${MAKE} -C libft fclean
	${RM} ${NAME}
	${MA}

re:     fclean all

.PHONY: all clean fclean re bonus f
