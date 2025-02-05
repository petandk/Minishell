# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpolo <gpolo@student.42barcelona.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/04 11:11:44 by gpolo             #+#    #+#              #
#    Updated: 2025/02/05 13:30:28 by gpolo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= minishell
 
LIBS			:= minishell.h

SRC_DIR			:= src/

OBJ_DIR			:= obj/

LIBS_DIRS		:= ./libs/libft
LIBS_A          := ./libs/libft/libft.a
LIBS_COM		:= readline termcap
LIBS_INC		:= $(addprefix -I , $(LIBS_DIRS))
LIBS_COML		:= $(addprefix -l, $(LIBS_COM))

#SRCS_FILES		:= 
SRCS_FILES		:= $(shell find $(SRC_DIR) -type f -iname "*.c" | sed 's#[.][^.]*$$##')
SRCS			:= $(addsuffix .c, $(SRCS_FILES))
SRCDIRS			:= $(shell find $(SRC_DIR) -type d)
OBJSDIRS		:= $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SRCDIRS))
OBJSTEMP		:= $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SRCS_FILES))
OBJS			:= $(addsuffix .o, $(OBJSTEMP))

CC				:= cc

CFLAGS			:= -Wall -Wextra -g $(LIBS_INC)

AR				:= ar rcs
RANLIB			:= ranlib
RM				:= rm -rf
MKDIR			:= mkdir -p

all:			makelibs $(NAME)

$(NAME):	    $(OBJSDIRS) $(OBJS) $(LIBS_A) Makefile
				$(CC) $(CFLAGS) $(OBJS) $(LIBS_A) $(LIBS_COML) -o $(NAME)
	
$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(LIBS) Makefile 
				$(CC) -I . $(CFLAGS) -c $< -o $@

$(OBJSDIRS):
				$(MKDIR) $(OBJSDIRS)

$(LIBS_A):
				for dir in $(LIBS_DIRS); do \
					$(MAKE) -C $$dir; \
				done
makelibs:
				for dir in $(LIBS_DIRS); do \
					$(MAKE) -C $$dir; \
				done
				

clean:
				$(RM) $(OBJS)
				for dir in $(LIBS_DIRS); do \
					$(MAKE) clean -C $$dir; \
				done

fclean:			clean
				$(RM) $(OBJSDIRS)
				$(RM) $(NAME)
				for dir in $(LIBS_DIRS); do \
					$(MAKE) fclean -C $$dir; \
				done

re:				fclean $(NAME)

normi:
				@norminette $(SRCS) $(LIBS)
info:
				$(info $(SRCS_FILES))

.PHONY:			all clean fclean re info normi
