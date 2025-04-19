CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = minishell

SRC_DIR = ./src
INCLUDE_DIR = ./include

SRCS = 	utils/minishell.c              \
		tokenizer/tokens_for_tokenizer.c   \
		expander/dollar_sign.c            \
		builtins/builtins.c               \
		expander/tokens.c                 \
		expander/count_tokens.c           \
		builtins/echo.c                   \
		builtins/env.c                    \
		builtins/export.c                 \
		expander/single_qouts.c           \
		expander/double_qouts.c           \
		executer/executer.c               \
		tokenizer/tokenizer.c              \
		executer/here_doc.c               \
		executer/add_cmd_after_pipe.c     \
		executer/checks_before_execute.c  \
		executer/execute_bulitin.c        \
		utils/signals.c                \
		expander/expander.c               \
		utils/minishell_utils.c        \
		tokenizer/tokenizer_utils1.c       \
		tokenizer/tokenizer_utils2.c       \
		tokenizer/tokenizer_utils3.c       \
		expander/Preparing_for_expander.c \
		expander/dollar_sign_utils1.c     \
		expander/dollar_sign_utils2.c     \
		expander/qouts_with_dollar.c      \
		expander/qouts_with_dollar_utils.c\
		expander/spaces_handler.c         \
		expander/spaces_handler_utils.c   \
		builtins/env_utils.c              \
		builtins/export_utils.c           \
		builtins/cd.c                     \
		executer/cmd_after_pipe_utils.c   \
		executer/executer_utils.c         \
		executer/absolute_path.c          \
		executer/executer_checks.c        \
		expander/tokens2.c                \
		executer/here_doc_utils.c         \
		tokenizer/tokenizer_utils4.c       \
		executer/exit_status_and_cmd.c    \
		executer/here_doc_prepration.c    \
		executer/redirection.c            \
		executer/checks_before_execute_utils.c\
		executer/execute_bulitin_utils.c  \
		executer/child_process.c


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


OBJ_DIR = OBJS
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
LIBFT_DIR = ./libft
READLINE_FLAGS = -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)$(BOLD)Linking the executable...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(READLINE_FLAGS) -o $(NAME)
	@echo "$(YELLOW)$(BOLD)Linking done!$(RESET)"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/minishell.h | $(OBJ_DIR)
	@echo "$(CYAN)$(BOLD)Compiling: $<$(RESET)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(RED)$(BOLD)Compilation of $< done!$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(GREEN)$(BOLD)Cleaning build...$(RESET)"
	@rm -f $(OBJS)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@echo "$(GREEN)$(BOLD)Build cleaned!$(RESET)"

fclean: clean
	@echo "$(GREEN)$(BOLD)Removing executable...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)$(BOLD)Executable removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
