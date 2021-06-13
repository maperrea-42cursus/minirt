# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/09 22:09:05 by maperrea          #+#    #+#              #
#    Updated: 2021/06/13 17:57:47 by maperrea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.h inc
vpath %.c src
vpath %.o obj

NAME			= miniRT

SRCDIR			= src

SRCS			= $(notdir $(shell find $(SRCDIR)/*.c))

OBJDIR			= obj

OBJS			= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

INCDIR			= inc

MLX				= libmlx.dylib

MLXDIR			= mlx

LIBFT			= libft.a

LIBDIR			= libft

CC				= gcc

RM				= rm -f

CFLAGS			= -Wall -Werror -Wextra

DEBUG			= #-g -fsanitize=address #-D CHECK_LEAKS

$(OBJDIR)/%.o: $(SRCDIR)/%.c
				@$(CC) $(DEBUG) -O3 $(CFLAGS) -I$(INCDIR) -c $^ -o $@

all:			$(NAME)

$(MLX):			
				make -C $(MLXDIR)
				cp $(MLXDIR)/$(MLX) .

$(LIBDIR)/$(LIBFT):
				make -C $(LIBDIR)

$(OBJDIR):
				@mkdir -p $(OBJDIR)

$(NAME):		$(MLX) $(LIBDIR)/$(LIBFT) $(OBJDIR) $(OBJS)
				$(CC) $(DEBUG) -O3 $(CFLAGS) -I$(INCDIR) $(OBJS) $(MLX) \
						$(LIBDIR)/$(LIBFT) $(GNLDIR)/$(GNL) -o $(NAME)

clean:
				$(RM) -r $(OBJDIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)
