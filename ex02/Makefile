# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 21:03:35 by rabril-h          #+#    #+#              #
#    Updated: 2023/11/15 21:32:57 by rabril-h         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = PmergeMe 


RM = rm -f
CC = c++
CFLAGS = -Werror -Wextra -Wall -std=c++98 -g -fsanitize=address


FILES = main ./classes/PmergeMe

SRC = $(addsuffix .cpp, $(FILES))

vpath %.cpp 


OBJ = $(SRC:.cpp=.o)
DEP = $(addsuffix .d, $(basename $(OBJ)))


%.o: %.cpp Makefile
	@${CC} $(CFLAGS) -MMD -c $< -o $@

all:
	@$(MAKE) $(NAME) --no-print-directory

$(NAME):: $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	@$(RM) $(OBJ) $(DEP) --no-print-directory
	@echo "Objects cleaned"

fclean: clean
	@$(RM) $(NAME) --no-print-directory
	@echo "All compilation files removed"

re:	fclean all

.PHONY: all clean fclean re

-include $(DEP)