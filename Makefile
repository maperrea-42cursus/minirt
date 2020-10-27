# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/09 22:09:05 by maperrea          #+#    #+#              #
#    Updated: 2020/10/27 18:05:27 by maperrea         ###   ########.fr        #
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

LIBFT			= libft.a

LIBDIR			= libft

GNL				= gnl.a

GNLDIR			= gnl

CC				= gcc

RM				= rm -f

CFLAGS			= -Wall -Werror -Wextra

DEBUG			= -g -fsanitize=address

$(OBJDIR)/%.o: $(SRCDIR)/%.c
				@$(CC) $(DEBUG) -O3 $(CFLAGS) -I$(INCDIR) -c $^ -o $@

all:			$(NAME)

$(MLX):			
				make -C $(MLXDIR)
				cp $(MLXDIR)/$(MLX) .

$(LIBDIR)/$(LIBFT):
				make -C $(LIBDIR)

$(GNLDIR)/$(GNL):
				make -C $(GNLDIR)

$(OBJDIR):
				@mkdir -p $(OBJDIR)

$(NAME):		$(MLX) $(LIBDIR)/$(LIBFT) $(GNLDIR)/$(GNL) $(OBJDIR) $(OBJS)
				$(CC) $(DEBUG) -O3 $(CFLAGS) -I$(INCDIR) $(OBJS) $(MLX) \
						$(LIBDIR)/$(LIBFT) $(GNLDIR)/$(GNL) -o $(NAME)

clean:
				$(RM) -r $(OBJDIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)
