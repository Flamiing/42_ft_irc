# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/27 19:25:47 by alaaouam          #+#    #+#              #
#    Updated: 2023/08/21 15:22:41 by alaaouam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	COLOURS	#

GREEN = \033[0:32m
COLOR_OFF = \033[0m

#	VARIABLES	#

NAME = ircserv

SRC =	
			
SRC_PATH = src/*/
SRCS = $(addprefix $(SRC_PATH), $(SRC))

OBJ_PATH = obj/
OBJ = $(SRC:.cpp=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

INC = inc/

CPP = c++
CPPFLAGS =  -Wall -Wextra -Werror -std=c++98
RM = rm -rf

#	RULES	#

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir -p $(OBJ_PATH)
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)
	@echo "$(GREEN)<+> $(NAME) has been created! <+>$(COLOR_OFF)"

clean:
	@$(RM) $(OBJ_PATH)

fclean: clean
	@$(RM) $(NAME)
	@echo "$(GREEN)<-> $(NAME) cleaned succesfuly! <->$(COLOR_OFF)"

re: fclean all

.PHONY: all clean fclean re