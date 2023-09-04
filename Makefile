# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/27 19:25:47 by alaaouam          #+#    #+#              #
#    Updated: 2023/09/04 12:21:43 by guilmira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	COLOURS	#

GREEN = \033[0:32m
COLOR_OFF = \033[0m

#	VARIABLES	#

NAME = ircserv

SRC =	main.cpp Server.cpp ServerRun.cpp ServerClientConnections.cpp ServerProcessMessage.cpp \
			   Client.cpp parsePort.cpp printError.cpp processCommand.cpp passCommand.cpp userCommand.cpp \
			   splitString.cpp nickCommand.cpp operCommand.cpp ServerChannelConnection.cpp ChannelConnection.cpp \
			   Channel.cpp joinCommand.cpp getMessage.cpp noticeCommand.cpp trimSpaces.cpp toUpperCase.cpp \
			   quitCommand.cpp ChannelDisconnection.cpp Command.cpp ServerClientDisconnection.cpp dieCommand.cpp \
			   channelUtils.cpp kickCommand.cpp ServerChannelDisconnection.cpp partCommand.cpp numberToString.cpp topicCommand.cpp\
			   ServerChannels.cpp
			
SRC_PATH = src/*/
SRCS = $(addprefix $(SRC_PATH), $(SRC))

OBJ_PATH = obj/
OBJ = $(SRC:.cpp=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

INC = inc/

CPP = c++
CPPFLAGS =  -Wall -Wextra -Werror -std=c++98 #-g3 -fsanitize=address
RM = rm -rf

#_GUILLE - ¿Que pasa si ejecutamos en un puerto en uso, 4242?
ARG1 = 2042
ARG2 = pass
CSANITIZE	= -fsanitize=address

#	RULES	#

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir -p $(OBJ_PATH)
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)<+> $(NAME) has been created! <+>$(COLOR_OFF)"

clean:
	@$(RM) $(OBJ_PATH)

fclean: clean
	@$(RM) $(NAME)
	@echo "$(GREEN)<-> $(NAME) cleaned succesfuly! <->$(COLOR_OFF)"



exe: $(OBJS)
	@$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)<+> $(NAME) executing at port '$(ARG1)' and with password: '$(ARG2)' <+>$(COLOR_OFF)"
	@./ircserv $(ARG1) $(ARG2)

san: $(OBJS)
	$(CPP) $(CPPFLAGSS) $(CSANITIZE) $(OBJS) -o $(NAME)
	@echo "$(GREEN)<+> $(NAME) compiled with fsanitize! <+>$(COLOR_OFF)"

net:
	nc -c localhost $(ARG1)
#echo "PASS pass"

net1:
	bash user.sh

re: fclean all

.PHONY: all clean fclean re