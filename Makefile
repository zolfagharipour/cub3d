NAME	=	cubid3d
INC		=	cubid.h
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
MLXFLAG	=	-lmlx -lXext -lX11 -g -lm
AR		=	ar rc
RM		=	rm -f

SRC		=	main.c setup_window_minimap.c events.c draw_red_square.c image.c

OBJ		=	$(SRC:.c=.o)

.PHONY:		all clean fclean re

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME)	$(MLXFLAG)

%.o: %.c	$(INC)
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			clean all