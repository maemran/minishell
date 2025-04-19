CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_two_d_dup.c ft_two_d_len.c ft_find_qouts.c ft_free_two_d_array.c\
ft_print_minishell.c ft_strncpy.c get_next_line.c ft_strlcat.c ft_split.c\
ft_split_cmd.c ft_strtrim.c ft_striteri.c ft_strmapi.c ft_strjoin.c ft_itoa.c\
ft_putnbr_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_putchar_fd.c \
ft_substr.c ft_strdup.c ft_calloc.c ft_memmove.c ft_isdigit.c ft_isalpha.c\
ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
ft_memcpy.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strncmp.c ft_memchr.c\
ft_memcmp.c ft_strrchr.c ft_strnstr.c ft_atoi.c ft_two_d_print.c ft_str_comp.c\
ft_atoi_ll.c ft_strlcpy_gnl.c ft_strlcpy.c

OBJS = $(SRCS:.c=.o)
SRCSOBJ = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c
NAME = libft.a
OBJ_B = $(SRCSOBJ:.c=.o)
all: $(NAME)

BOLD = \033[1m
BLACK = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE =  \033[37m
RESET = \033[0m

$(NAME): $(OBJS)
	@echo "$(BOLD)$(GREEN)Creating $(NAME)$(RESET)"
	@ar rcs $(NAME) $(OBJS)
	@echo "$(BOLD)$(GREEN)$(NAME) created!$(RESET)"

%.o: %.c
	@echo "$(BOLD)$(CYAN)Compiling $<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BOLD)$(RED)Compilation of $< done!$(RESET)"

bonus : $(OBJS) $(OBJ_B)
	@echo "$(BOLD)$(GREEN)Creating $(NAME)$(RESET)"
	@ar rcs $(NAME) $(OBJ_B) $(OBJS)
	@echo "$(BOLD)$(GREEN)$(NAME) created!$(RESET)"

clean:
	@echo "$(BOLD)$(RED)Cleaning up...$(RESET)"
	@rm -f $(OBJS) $(OBJ_B)
	@echo "$(BOLD)$(RED)Cleaned up!$(RESET)"

fclean: clean
	@echo "$(BOLD)$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@echo "$(BOLD)$(RED)$(NAME) removed!$(RESET)"

re: fclean all

.PHONY: re fclean clean bonus all
