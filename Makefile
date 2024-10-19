CC = cc
CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF_DIR = ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
SERVER = server
CLIENT = client
NAME = $(SERVER) $(CLIENT)

SERVER_SRCS = server.c
CLIENT_SRCS = client.c
SRCS = $(SERVER_SRCS) $(CLIENT_SRCS)

SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
OBJS = $(SERVER_OBJS) $(CLIENT_OBJS)

all: $(LIBFT) $(FT_PRINTF) $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJS) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_OBJS) $(LIBFT) $(FT_PRINTF)

$(CLIENT): $(CLIENT_OBJS) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_OBJS) $(LIBFT) $(FT_PRINTF)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(FT_PRINTF):
	make -C $(FT_PRINTF_DIR)

clean:
	$(RM) $(NAME) $(OBJS)
	make clean -C $(LIBFT_DIR)
	make clean -C $(FT_PRINTF_DIR)

fclean: clean
	$(RM) $(NAME) $(OBJS)
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(FT_PRINTF_DIR)

re: all clean fclean re

.PHONY: all clean fclean re
