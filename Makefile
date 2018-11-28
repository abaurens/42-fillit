# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/27 16:23:33 by abaurens          #+#    #+#              #
#    Updated: 2018/11/28 19:41:24 by abaurens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC          =   gcc
RM          =   rm -rf
CP          =   cp -rf
LINKER      =   gcc
NAME        =   fillit
LIB         =   libft
SRCD        =   srcs
OBJD        =   objs

SRC         =   main.c      \
                memory.c    \
				math.c		\
                system.c

CFLAGS      +=  -I./includes -W -Wall -Wextra -ansi # -pedantic -Werror
OBJ         :=  $(addprefix $(OBJD)/,$(SRC:.c=.o))
SRC         :=  $(addprefix $(SRCD)/,$(SRC))
LIB_DIR     :=  $(shell find . -type d -name '$(LIB)')

ifneq ($(LIB_DIR),)
CFLAGS      +=  -I$(LIB_DIR)/includes
LDFLAGS     +=  -L$(LIB_DIR) -lft
endif

$(NAME):    $(OBJ)
ifneq ($(LIB_DIR),)
	@make -C $(LIB_DIR)
endif
	$(LINKER) $(LDFLAGS) -o $(NAME) $(OBJ)

objs/%.o:   $(SRCD)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

all:    $(NAME)

clean:
ifneq ($(LIB_DIR),)
	@make -C $(LIB_DIR) clean
endif
	$(RM) $(OBJD)

fclean:
ifneq ($(LIB_DIR),)
	@make -C $(LIB_DIR) fclean
endif
	$(RM) $(OBJD)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
