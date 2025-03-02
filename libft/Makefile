CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_free_two_d_array.c ft_print_minishell.c ft_strncpy.c get_next_line.c ft_strlcat.c ft_split.c ft_split_cmd.c ft_strtrim.c ft_striteri.c ft_strmapi.c ft_strjoin.c ft_itoa.c ft_putnbr_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_strlcpy.c ft_substr.c ft_strdup.c ft_calloc.c ft_memmove.c ft_isdigit.c ft_isalpha.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strrchr.c ft_strnstr.c ft_atoi.c  
OBJS = $(SRCS:.c=.o)
SRCSOBJ = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c
NAME = libft.a
OBJ_B = $(SRCSOBJ:.c=.o)
all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus : $(OBJS) $(OBJ_B)
	ar rcs $(NAME) $(OBJ_B) $(OBJS)

clean:
	rm -f $(OBJS) $(OBJ_B)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean bonus all
