# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/11 02:43:12 by ebelfkih          #+#    #+#              #
#    Updated: 2023/03/11 22:05:56 by ebelfkih         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
ONAME = pipex.a 
MAIN = code/pipex.c
CC = cc -Wall -Werror -Wextra
RM = rm -f
AR = ar rc
FILES = code/parsing.c utils/libft_utils.c utils/libft_utils2.c utils/libft_utils3.c
OBJ = $(FILES:.c=.o)

RED = \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[0;35m


all : $(ONAME) $(NAME)
	@echo "${GREEN} archieve files are created"
	@echo "${PURPLE} executable file is created"

$(NAME) : $(ONAME)
	$(CC) $(MAIN) $(ONAME) -o $(NAME)

$(ONAME) : $(OBJ)
	$(AR) $(ONAME) $^

%.o : %.c header/pipex.h
	$(CC) -o $@ -c $<

clean :
	$(RM) $(OBJ) $(ONAME)
	echo "${RED} archieve files are removed"


fclean: clean
	$(RM) $(NAME) $(ONAME)
	echo "${RED} executable file removed"

re: fclean all

.PHONY = clean fclean re