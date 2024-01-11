NAME			:= pipex

CC				:= cc
CFLAGS			:= -g -Wall -Wextra -Werror
RM				:= rm -rf

LIBFT_DIR		:= ./libft/
LIBFT_DIR_MAIN	:= ./libft/libft/
LIBFT			:= $(LIBFT_DIR)/libft.a
HEADERS_DIR		:= ./headers/

SRCS_PATH		:= ./srcs/
SRCS_CORE		:= pipex.c core.c free_modify.c utils.c
SRCS_BONUS		:= pipex_bonus.c core_bonus.c free_modify_bonus.c utils_bonus.c

HEADERS			:= -I$(HEADERS_DIR)
HEADERS_CORE 	:= $(HEADERS_DIR)/get_next_line.h $(HEADERS_DIR)/libft.h $(HEADERS_DIR)/pipex.h
HEADERS_BONUS 	:= $(HEADERS_DIR)/get_next_line.h $(HEADERS_DIR)/libft.h $(HEADERS_DIR)/pipex_bonus.h

OBJS_CORE		:= $(SRCS_CORE:.c=.o)
OBJS_BONUS		:= $(SRCS_BONUS:.c=.o)

OBJS			:= $(addprefix $(SRCS_PATH), $(OBJS_CORE))
OBJS_BONUS		:= $(addprefix $(SRCS_PATH), $(OBJS_BONUS))
SRCS			:= $(addprefix $(SRCS_PATH), $(SRCS_CORE))
SRCS_BONUS		:= $(addprefix $(SRCS_PATH), $(SRCS_BONUS))

GREEN			:= \033[0;32m
BLUE			:= \033[0;34m
NC				:= \033[0m

all: $(NAME)

$(NAME): $(SRCS) $(OBJS) $(LIBFT) $(HEADERS_CORE) .base
	@$(CC) $(CFLAGS) $(HEADERS) $(SRCS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)--- Compilation of '$(NAME)' completed successfully ---$(NC)"

.base:
	@$(RM) .bonus
	@touch .base

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: .bonus

.bonus: $(SRCS_BONUS) $(OBJS_BONUS) $(LIBFT) $(HEADERS_BONUS)
	@$(CC) $(CFLAGS) $(HEADERS) $(SRCS_BONUS) $(LIBFT) -o $(NAME)
	@$(RM) .base
	@touch .bonus
	@echo "$(GREEN)--- Compilation of '$(NAME)' completed successfully ---$(NC)"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@$(RM) $(NAME) .bonus
	@$(RM) $(NAME) .base
	@$(RM) $(OBJS) $(OBJS_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(BLUE)--- Object files from libft cleaned ---$(NC)"

fclean: clean
	@echo "$(BLUE)--- '$(NAME)' removed ---$(NC)"
	@make -C $(LIBFT_DIR) fclean
	@echo "$(BLUE)--- Cleaning finished ---$(NC)"

re: fclean all
	@echo "$(GREEN)--- Everything recompiled ---$(NC)"

.PHONY: all clean fclean re