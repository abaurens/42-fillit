# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/27 16:23:33 by abaurens          #+#    #+#              #
#    Updated: 2018/12/03 16:39:52 by abaurens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC          =   gcc -xc
RM          =   rm -rf
CP          =   cp -rf
LINKER      =   gcc
NAME        =   fillit
LIB         =   libft
SRCD        =   srcs
OBJD        =   objs

SRC         =   process.c		\
				ft_sqrt.c		\
				post_parse.c	\
				simple_parse.c	\
				post_process.c

CFLAGS      +=  -I./includes -g -Wall -Wextra -Werror

OBJ         :=  $(addprefix $(OBJD)/,$(SRC:.c=.o))
SRC         :=  $(addprefix $(SRCD)/,$(SRC))

$(NAME):    $(OBJ)
	$(LINKER) -o $(NAME) $(OBJ) $(LDFLAGS)

$(OBJD)/%.o:   $(SRCD)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

all:    $(NAME)

clean:
	$(RM) $(OBJD)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
