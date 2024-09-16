# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdukuray <gdukuray@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 11:37:04 by gdukuray          #+#    #+#              #
#    Updated: 2023/01/30 15:31:28 by gdukuray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= main.c \
		init.c \
		init_mutex.c \
		utils.c \
 		philo.c \
  		philo_eat.c \
  		die_or_end.c \
    	check_mutex.c 
	 	 

OBJS	= $(SRCS:.c=.o)

NAME	= philo

CLANG	= clang

FLAGS	= -Wall -Wextra -Werror -g3

INCLUDE	= -lpthread

HEADER	= philo.h

all:	$(NAME)

.PHONY:	clean fclean re bonus 

$(NAME): $(OBJS)
	$(CLANG) $(INCLUDE) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(B_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

%.o: %.c $(HEADER)
	$(CLANG) $(FLAGS) -c $<  -o $(<:.c=.o)
