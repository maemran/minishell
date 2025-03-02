CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = minishell
SRCS = minishell.c tokens_for_tokenizer.c  dollar_sign.c ft_builtins.c tokens.c\
 single_qouts.c double_qouts.c count_tokens.c
OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ./libft
READLINE_FLAGS = -lreadline

all: $(NAME)

$(NAME): $(OBJS) 
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(READLINE_FLAGS) -o $(NAME) 

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re