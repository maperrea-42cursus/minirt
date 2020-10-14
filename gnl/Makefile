# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/14 18:27:05 by maperrea          #+#    #+#              #
#    Updated: 2020/10/14 18:35:53 by maperrea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= gnl.a

SRCS			= get_next_line.c get_next_line_utils.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc

AR				= ar rc

RM				= rm -f

CFLAGS			= -Wall -Werror -Wextra

.c.o:
				$(CC) $(CFLAGS) -c $^ -o $@

all:			$(NAME)

$(NAME):		$(OBJS)
				$(AR) $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all
