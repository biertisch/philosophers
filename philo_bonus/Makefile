NAME		=	philo_bonus

SRC_FILES	=	exit init main monitor print routine time validate

SRC_DIR		=	src/
OBJ_DIR		=	obj/
INC_DIR		=	include/

SRC			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ         =	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g -I$(INC_DIR)
RM			=	rm -rf

SENTINEL	=	$(OBJ_DIR).compiled

all: $(NAME)
	@cat ../banner.txt

$(NAME): $(OBJ)
	@echo "Linking executable..."
	@$(CC) $(OBJ) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ): $(SENTINEL)

$(SENTINEL):
	@echo "Compiling object files..."
	@touch $@

clean:
	@echo "Removing object files..."
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "Removing executable..."
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re