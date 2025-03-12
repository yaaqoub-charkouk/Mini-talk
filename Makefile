CC = cc
CFLAGS = -Wall -Werror -Wextra
C_OBJ = src/client.o 
S_OBJ = src/server.o 
U_OBJ = utils/ft_atoi.o utils/ft_printf.o utils/ft_printf_utils.o utils/list_utils.o

C_B_OBJ = bonus/client_bonus.o 
S_B_OBJ = bonus/server_bonus.o 

all: .mandatory

.mandatory: $(C_OBJ) $(S_OBJ) $(U_OBJ)
	@touch .mandatory
	@rm -rf .bonus
	$(CC) $(CFLAGS) $(C_OBJ) $(U_OBJ) -o client
	$(CC) $(CFLAGS) $(S_OBJ) $(U_OBJ) -o server

src/%.o: src/%.c mini_talk.h
	$(CC) $(CFLAGS) -c $< -o $@

utils/%.o: utils/%.c utils/utils.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus: .bonus

.bonus: $(C_B_OBJ) $(S_B_OBJ) $(U_OBJ)
	@touch .bonus
	@rm -rf .mandatory
	$(CC) $(CFLAGS) $(C_B_OBJ) $(U_OBJ) -o client
	$(CC) $(CFLAGS) $(S_B_OBJ) $(U_OBJ) -o server

bonus/%.o: bonus/%.c bonus/mini_talk_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(C_OBJ) $(S_OBJ) $(U_OBJ) $(C_B_OBJ) $(S_B_OBJ) $(U_OBJ) .bonus .mandatory

fclean: clean
	rm -rf client server

re: fclean all
	
.PHONY: all clean fclean re bonus
