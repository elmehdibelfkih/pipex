# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/11 02:43:12 by ebelfkih          #+#    #+#              #
#    Updated: 2023/03/16 15:56:39 by ebelfkih         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipex_bonus
ONAME = pipex.a 
MAIN = main/pipex.c
BONUS_MAIN = main/pipex_bonus.c
CC = cc -Wall -Werror -Wextra
RM = @rm -f
AR = @ar rc
IN_OUT = @touch input output
FILES = functions/parsing.c functions/pipex_utils.c functions/pipex_utils2.c utils/libft_utils.c utils/libft_utils2.c utils/get_next_line.c
OBJ = $(FILES:.c=.o)

RED = \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[0;35m


%.o : %.c header/pipex.h
	$(CC) -o $@ -c $<

all : $(ONAME) $(BONUS_NAME) $(NAME) inout
	@echo "${GREEN} archive files are created"
	@echo "${GREEN} input, output files are created"
	@echo "${PURPLE} executable files are created"
	@echo "${PURPLE} bonus executable file is created"

$(NAME) : $(ONAME)
	$(CC) $(MAIN) $(ONAME) -o $(NAME)

$(BONUS_NAME) : $(ONAME)
	$(CC) $(BONUS_MAIN) $(ONAME) -o $(BONUS_NAME)

$(ONAME) : $(OBJ)
	@echo "${GREEN} start archiving"
	$(AR) $(ONAME) $^

mandatory : $(NAME)
	@echo "${GREEN} start compiling"
	@echo "${GREEN} archive files are created"
	@echo "${PURPLE} executable files are created"

clean :
	$(RM) $(OBJ) $(ONAME)
	@echo "${RED} archive files are removed"
	
bonus : $(ONAME) $(BONUS_NAME)
	@echo "${GREEN} start compiling"
	@echo "${GREEN} archive files are created"
	@echo "${PURPLE} bonus executable file is created"

fclean: clean
	$(RM) $(NAME) $(ONAME) $(BONUS_NAME) $(IN_OUT)
	@echo "${RED} executable file removed"
	@echo "${RED} input, output files removed"

inout:
	$(IN_OUT)

re: fclean all 

.PHONY: clean fclean re bonus all inout mandatory
