# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arolland <arolland@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/30 14:55:17 by arolland          #+#    #+#              #
#    Updated: 2022/01/10 15:52:14 by arolland         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c \
utils.c \
mutex.c \
thread.c \
action.c \
init.c \
check.c \

OBJS = ${SRCS:.c=.o}
DEPS = ${OBJS:.o=.d}

HEADER = philo.h

NAME = philo

CC = clang 

CFLAGS = -Wall -Wextra -Werror -pthread -MMD -MP -ggdb3 #-fsanitize=thread

RM = rm -f

all: ${NAME}

-include $(DEPS)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -I$(HEADER) -c $< -o $@

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME} ${DEPS}

re: fclean all

.PHONY: all clean fclean re
