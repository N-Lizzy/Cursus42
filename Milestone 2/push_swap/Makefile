NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -Ilibft

# ===================== DIRECTORIOS =====================

OP      = operations/
UTILS   = utils/
LIBFT_DIR = libft

OBJDIR  = obj/

# ===================== LIBFT ===========================

LIBFT = $(LIBFT_DIR)/libft.a

# ===================== SOURCES =========================

SRC = \
push_swap.c \
$(OP)push.c $(OP)reverse_rotate.c $(OP)rotate.c $(OP)swap.c \
$(UTILS)free_utils.c $(UTILS)parse_utils.c $(UTILS)size_utils.c $(UTILS)utils.c

OBJ = $(SRC:%.c=$(OBJDIR)%.o)

# ===================== RULES ============================

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJDIR)%.o: %.c push_swap.h
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
