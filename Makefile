# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/09 22:09:05 by maperrea          #+#    #+#              #
#    Updated: 2020/10/09 22:30:17 by maperrea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.h inc
vpath %.c src
vpath %.o obj

NAME			= minirt

SRCDIR			= src

SRCS			= $(notdir $(shell find $(SRCDIR)/*.c))

OBJDIR			= obj

OBJS			= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

INCDIR			= inc

MLX				= libmlx.dylib

MLXDIR			= mlx

CC				= gcc

RM				= rm -f

CFLAGS			= -Wall -Werror -Wextra

$(OBJDIR)/%.o: $(SRCDIR)/%.c
				@$(CC) -O3 $(CFLAGS) -I$(INCDIR) -c $^ -o $@

all:			$(NAME)

$(MLXDIR)/$(MLX):			
				make -C $(MLXDIR)

$(OBJDIR):
				@mkdir -p $(OBJDIR)

$(NAME):		$(MLXDIR)/$(MLX) $(OBJDIR) $(OBJS)
				$(CC) -O3 $(CFLAGS) -I$(INCDIR) $(OBJS) $(MLXDIR)/$(MLX) -o $(NAME)

clean:
				$(RM) -r $(OBJDIR)

fclean:
				$(RM) $(NAME)

re:				fclean $(NAME)
