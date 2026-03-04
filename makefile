NAME	=	my_ping

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
DEPFLAGS=	-MMD -MP

INC_DIR	=	include
SRC_DIR	=	src
OBJ_DIR	=	obj

INCLUDES =	-I$(INC_DIR)

SRCS	=	$(wildcard $(SRC_DIR)/*.c)
OBJS	=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS	=	$(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lm

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re