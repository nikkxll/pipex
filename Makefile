NAME			:= pipex

CC				:= cc
CFLAGS			:= -g -Wall -Wextra -Werror

LIBFT_DIR		:= ./libft/
LIBFT_DIR_MAIN	:= ./libft/libft/
SRCS_PATH		:= ./srcs/
LIBFT			:= $(LIBFT_DIR)/libft.a
FDF_HEADER		:= pipex.h
LIBFT_HEADER	:= $(LIBFT_DIR)/libft.h
GNL_HEADER		:= $(LIBFT_DIR)/libft/get_next_line.h 

SRCS_CORE		:= main.c

HEADERS			:= -I$(LIBFT_DIR) -I$(LIBFT_DIR)/libft -I$(LIBFT_DIR)/libft/get_next_line.h

OBJS_LIBFT		:= $(SRCS_LIBFT:.c=.o)

OBJS			:= $(addprefix $(LIBFT_DIR_MAIN), $(OBJS_LIBFT))

SRCS			:= $(addprefix $(SRCS_PATH), $(SRCS_CORE))

GREEN			:= \033[0;32m
BLUE			:= \033[0;34m
NC				:= \033[0m

all: $(NAME)

$(NAME): $(SRCS) $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(HEADERS) -o $(NAME)
	@echo "$(GREEN)---Compilation of '$(NAME)' completed successfully ---$(NC)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS) 

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(BLUE)--- Object files from libft cleaned ---$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(BLUE)--- '$(NAME)' removed ---$(NC)"
	@make -C $(LIBFT_DIR) fclean
	@echo "$(BLUE)--- Cleaning finished ---$(NC)"

re: fclean all
	@echo "$(GREEN)--- Everything recompiled ---$(NC)"

.PHONY: all clean fclean re