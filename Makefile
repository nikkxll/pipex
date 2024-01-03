NAME			:= pipex

CC				:= cc
CFLAGS			:= -g -Wall -Wextra -Werror
RM				:= rm -rf

LIBFT_DIR		:= ./libft/
LIBFT_DIR_MAIN	:= ./libft/libft/
LIBFT			:= $(LIBFT_DIR)/libft.a
HEADERS_DIR		:= ./headers/

SRCS_PATH		:= ./srcs/
SRCS_CORE		:= main.c core.c error_messages.c validators.c

HEADERS			:= -I$(HEADERS_DIR)
HEADERS_ALL 	:= $(HEADERS_DIR)/get_next_line.h $(HEADERS_DIR)/libft.h $(HEADERS_DIR)/pipex.h

OBJS_CORE		:= $(SRCS_CORE:.c=.o)

OBJS			:= $(addprefix $(SRCS_PATH), $(OBJS_CORE))
SRCS			:= $(addprefix $(SRCS_PATH), $(SRCS_CORE))

GREEN			:= \033[0;32m
BLUE			:= \033[0;34m
NC				:= \033[0m

all: $(NAME)

$(NAME): $(SRCS) $(OBJS) $(LIBFT) $(HEADERS_ALL)
	@$(CC) $(CFLAGS) $(HEADERS) $(SRCS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)--- Compilation of '$(NAME)' completed successfully ---$(NC)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(BLUE)--- Object files from libft cleaned ---$(NC)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(BLUE)--- '$(NAME)' removed ---$(NC)"
	@make -C $(LIBFT_DIR) fclean
	@echo "$(BLUE)--- Cleaning finished ---$(NC)"

re: fclean all
	@echo "$(GREEN)--- Everything recompiled ---$(NC)"

.PHONY: all clean fclean re