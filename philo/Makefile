NAME = philo

SRC_DIR = src/
SRC = $(addprefix $(SRC_DIR),\
		exit.c init.c main.c monitor.c print.c routine.c time.c	validate.c)

OBJ_DIR = obj/
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -Iinclude -pthread
LFLAGS = -pthread
RM = rm -rf

all: $(NAME)

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