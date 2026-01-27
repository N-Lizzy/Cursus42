NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I.

# ===================== DIRECTORIOS =====================

IS      = is/
TO      = to/
MEM     = mem/
STR     = str/
PUTFD   = put_fd/
LST     = lst/
FTPRINTF  = ftprintf/
MISC    = misc/

OBJDIR  = obj/

# ===================== SOURCES =========================

SRC = \
$(IS)ft_isalnum.c $(IS)ft_isalpha.c $(IS)ft_isascii.c $(IS)ft_isdigit.c $(IS)ft_isprint.c \
$(TO)ft_tolower.c $(TO)ft_toupper.c \
$(MEM)ft_bzero.c $(MEM)ft_memchr.c $(MEM)ft_memcmp.c $(MEM)ft_memcpy.c $(MEM)ft_memmove.c $(MEM)ft_memset.c \
$(STR)ft_split.c $(STR)ft_strchr.c $(STR)ft_strdup.c $(STR)ft_striteri.c $(STR)ft_strjoin.c \
$(STR)ft_strlcat.c $(STR)ft_strlcpy.c $(STR)ft_strlen.c $(STR)ft_strmapi.c $(STR)ft_strncmp.c \
$(STR)ft_strnstr.c $(STR)ft_strrchr.c $(STR)ft_strtrim.c $(STR)ft_substr.c \
$(PUTFD)ft_putchar_fd.c $(PUTFD)ft_putendl_fd.c $(PUTFD)ft_putnbr_fd.c $(PUTFD)ft_putstr_fd.c \
$(LST)ft_lstnew.c $(LST)ft_lstadd_front.c $(LST)ft_lstsize.c $(LST)ft_lstlast.c \
$(LST)ft_lstadd_back.c $(LST)ft_lstdelone.c $(LST)ft_lstclear.c $(LST)ft_lstiter.c $(LST)ft_lstmap.c \
$(FTPRINTF)ft_printf.c $(FTPRINTF)ft_putchar_len.c $(FTPRINTF)ft_putstr_len.c $(FTPRINTF)ft_putnbr_len.c \
$(FTPRINTF)ft_puthexa_len.c $(FTPRINTF)ft_putunsigned_len.c $(FTPRINTF)ft_putpointer_len.c \
$(MISC)ft_atoi.c $(MISC)ft_calloc.c $(MISC)ft_itoa.c

OBJ = $(SRC:%.c=$(OBJDIR)%.o)

# ===================== RULES ============================

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJDIR)%.o: %.c libft.h
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
