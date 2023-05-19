# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 11:26:21 by ecamara           #+#    #+#              #
#    Updated: 2023/05/19 14:39:32 by ecamara          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Compiler
CC = clang++
CPPFLAGS = -std=c++17 -Wall -Wextra -O2# -g3 -fsanitize=address

SRC_FILES =	src/main.cpp\
			src/Server.cpp\
			src/Data.cpp\
			src/User.cpp

OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Libraries
INCLUDES = -I./libraries
STATIC_LIB = ../libraries/UDP/UdpConnection.a
#LIBS = -L./../libraries/mlx -lmlx -framework OpenGL -framework AppKit
#INCLUDES = -I/usr/local/include -I/Users/ecamara/.brew/include


NAME = server

all: $(NAME)

$(NAME): $(OBJ_FILES) $(STATIC_LIB)
	$(CC) $(CPPFLAGS) $(INCLUDES) $(STATIC_LIB) $^ -o $@

%.o: %.cpp
	$(CC) $(CPPFLAGS) $(INCLUDES) -c $^ -o $@

clean:
	rm -f $(OBJ_FILES) $(NAME)

re: clean all

.PHONY: all clean re