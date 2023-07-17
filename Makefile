# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrinna <jrinna@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 17:13:50 by jrinna            #+#    #+#              #
#    Updated: 2023/07/17 13:16:26 by jrinna           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

#### LIST ####
LST_SRC := action.c death.c philo.c 
LST_OBJ := $(LST_SRC:.c=.o)
LST_INC := philo.h 
#### LIST ####

#### DIRECTORY ####
DIR_SRC := source
DIR_OBJ := .object
DIR_INC := include
#### DIRECTORY ####

#### COMPLETE_PATH ####
SRC := $(addprefix $(DIR_SRC)/,$(LST_SRC))
OBJ := $(addprefix $(DIR_OBJ)/,$(LST_OBJ))
INC := $(addprefix $(DIR_INC)/,$(LST_INC))
#### COMPLETE_PATH ####

#### OTHER ####
CC := gcc
CFLAGS := -Wall -Wextra -Werror
NAME := philo
#### OTHER ####

#### STANDARD_RULE ####
all : $(NAME)

re : fclean all

clean :
	rm -rf $(DIR_OBJ)
	
fclean : clean
	rm -rf $(NAME)
#### STANDARD_RULE ####

#### CUSTOM_RULE ####
$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(NAME) -lpthread

$(DIR_OBJ)/%.o : $(DIR_SRC)/%.c $(INC) Makefile | $(DIR_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(DIR_INC)

$(DIR_OBJ) :
	mkdir -p $(DIR_OBJ)
#### CUSTOM_RULE ####

#### UTILS ####
.PHONY : all re clean fclean
#### UTILS ####
