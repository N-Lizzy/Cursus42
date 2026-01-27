NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = ft_printf.c ft_putchar.c ft_putstr.c ft_putnbr.c ft_puthexa.c ft_putunsigned.c ft_putpointer.c

OBJ = $(SRC:.c=.o)
HEADERS = ft_printf.h

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus