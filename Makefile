# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/11 02:43:12 by ebelfkih          #+#    #+#              #
#    Updated: 2023/03/15 04:12:07 by ebelfkih         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipex_bonus
ONAME = pipex.a 
MAIN = main/pipex.c
BONUS_MAIN = main/pipex_bonus.c
CC = cc -Wall -Werror -Wextra
RM = rm -f
AR = ar rc
FILES = functions/parsing.c functions/pipex_utils.c functions/pipex_utils2.c utils/libft_utils.c utils/libft_utils2.c
OBJ = $(FILES:.c=.o)

RED = \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[0;35m


all : $(ONAME) $(NAME)
	@echo "${GREEN} archieve files are created"
	@echo "${PURPLE} executable file is created"

$(NAME) : $(ONAME)
	$(CC) $(MAIN) $(ONAME) -o $(NAME)

$(BONUS_NAME) : $(ONAME)
	$(CC) $(BONUS_MAIN) $(ONAME) -o $(BONUS_NAME)

$(ONAME) : $(OBJ)
	$(AR) $(ONAME) $^

%.o : %.c header/pipex.h
	$(CC) -o $@ -c $<

clean :
	$(RM) $(OBJ) $(ONAME)
	echo "${RED} archieve files are removed"
	
bonus : $(ONAME) $(BONUS_NAME)
	@echo "${GREEN} archieve files are created"
	@echo "${PURPLE} executable file is created"

fclean: clean
	$(RM) $(NAME) $(ONAME) $(BONUS_NAME)
	echo "${RED} executable file removed"

re: fclean all

.PHONY = clean fclean re