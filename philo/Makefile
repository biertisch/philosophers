NAME		=	philo

SRC_FILES	=	exit init main monitor print routine time validate

SRC_DIR		=	src/
OBJ_DIR		=	obj/
INC_DIR		=	include/

SRC			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ         =	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g -I$(INC_DIR) -pthread
LFLAGS		=	-pthread
RM			=	rm -rf

all: $(NAME)
	@cat ../banner.txt

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(LFLAGS) $(OBJ) -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re