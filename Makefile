# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/09 22:09:05 by maperrea          #+#    #+#              #
#    Updated: 2020/10/13 20:24:10 by maperrea         ###   ########.fr        #
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

CC				= gcc

RM				= rm -f

CFLAGS			= -Wall -Werror -Wextra

$(OBJDIR)/%.o: $(SRCDIR)/%.c
				@$(CC) -O3 $(CFLAGS) -I$(INCDIR) -c $^ -o $@

all:			$(NAME)

$(MLX):			
				make -C $(MLXDIR)
				cp $(MLXDIR)/$(MLX) .

$(LIBDIR)/$(LIBFT):
				make -C $(LIBDIR)

$(OBJDIR):
				@mkdir -p $(OBJDIR)

$(NAME):		$(MLX) $(LIBDIR)/$(LIBFT) $(OBJDIR) $(OBJS)
				$(CC) -O3 $(CFLAGS) -I$(INCDIR) $(OBJS) $(MLX) $(LIBDIR)/$(LIBFT) -o $(NAME)

clean:
				$(RM) -r $(OBJDIR)

fclean:
				$(RM) $(NAME)

re:				fclean $(NAME)
