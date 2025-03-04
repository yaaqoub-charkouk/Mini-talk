CC = cc
CFLAGS = -Wall -Werror -Wextra
C_OBJ = src/client.o 
S_OBJ = src/server.o 
U_OBJ = utils/ft_atoi.o utils/ft_printf.o utils/ft_printf_utils.o

C_B_OBJ = bonus/client_bonus.o 
S_B_OBJ = bonus/server_bonus.o 

all: client server

client: $(C_OBJ) $(U_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

server: $(S_OBJ) $(U_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

src/%.o: src/%.c mini_talk.h
	$(CC) $(CFLAGS) -c $< -o $@

utils/%.o: utils/%.c utils/ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus: client_bonus server_bonus

client_bonus: $(C_B_OBJ) $(U_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

server_bonus: $(S_B_OBJ) $(U_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

bonus/%.o: bonus/%.c mini_talk_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(C_OBJ) $(S_OBJ) $(U_OBJ) $(C_B_OBJ) $(U_OBJ)

fclean: clean
	rm -rf client server client_bonus server_bonus

re: fclean all
	
.PHONY: all clean
