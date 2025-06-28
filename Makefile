
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zweng <zweng@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/19 12:41:50 by zweng             #+#    #+#              #
#    Updated: 2025/06/27 22:44:41 by wengzhang        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----- varaibles -----

CC 			= g++
NAME 		= libftpp.a

# ---------------- transformation ------------------ #

SRCS =		data_buffer.cpp \
			memento.cpp


OBJS = $(SRCS:.cpp=.o)

FLAGS 		=  -Wall -Wextra -Werror \
			   -std=c++11

DEBUGF 		= #-fsanitize=address -g

# ----- Colors -----
BLACK		:="\033[1;30m"
RED			:="\033[1;31m"
GREEN		:="\033[1;32m"
PURPLE		:="\033[1;35m"
CYAN		:="\033[1;36m"
WHITE		:="\033[1;37m"
EOC			:="\033[0;0m"
#  # ==================

# ----- part rules -----
all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs  $(NAME) $(OBJS) 
	@printf $(GREEN)"$(NAME) archiving\n"$(EOC)


%.o:%.cpp 
	@printf $(GREEN)"compiling %s\n"$(EOC) $@
	@$(CC) $(FLAGS) -o $@ -c $<

clean: 
	@rm -f $(OBJS) &2>/dev/null
	@rm main.o &2>/dev/null
	@printf $(GREEN)"$(NAME) clean\n"$(EOC)


fclean: clean
	@/bin/rm -f $(NAME) &2>/dev/null
	@rm main &2>/dev/null
	@printf $(GREEN)"$(NAME) fclean\n"$(EOC)

test: all
	@$(CC) -c $(main) -I. -std=c++11 -o main.o
	@$(CC) main.o -I. -L. -lftpp -std=c++11 -o main
	@./main

re: fclean all

.PHONY: clean fclean re norme all
