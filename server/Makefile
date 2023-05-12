# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 11:26:21 by ecamara           #+#    #+#              #
#    Updated: 2023/05/11 18:15:19 by ecamara          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Compiler
CC = clang++
CPPFLAGS = -std=c++17 -Wall -Wextra -O2

SRC_FILES =	src/main.cpp\
			src/Server.cpp\
			src/Data.cpp\
			src/User.cpp

OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Libraries
INCLUDES = -I./libraries
#LIBS = -L./../libraries/mlx -lmlx -framework OpenGL -framework AppKit
#INCLUDES = -I/usr/local/include -I/Users/ecamara/.brew/include


NAME = server

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CPPFLAGS) $(OBJ_FILES) $(INCLUDES) -o $@

%.o: %.cpp
	$(CC) $(CPPFLAGS) $(INCLUDES) -c $^ -o $@

clean:
	rm -f $(OBJ_FILES) $(NAME)

re: clean all

.PHONY: all clean re