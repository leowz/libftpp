
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zweng <zweng@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/19 12:41:50 by zweng             #+#    #+#              #
#    Updated: 2025/05/01 22:22:37 by zweng            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----- varaibles -----

CC 			= g++
NAME 		= libftpp.a

# ---------------- transformation ------------------ #

SRCS = 

OBJS = $(SRCS:.cpp=.o)

FLAGS 		=  -Wall -Wextra -Werror \
			   -std=c++20

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
	@rm -f $(OBJS)
	@printf $(GREEN)"$(NAME) clean\n"$(EOC)
	@make -C $(LIB_PATH) clean


fclean: clean
	@/bin/rm -f $(NAME)
	@printf $(GREEN)"$(NAME) fclean\n"$(EOC)

test:
	echo $(arg1)

re: fclean all

.PHONY: clean fclean re norme all
