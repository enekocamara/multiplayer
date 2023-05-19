# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 12:59:03 by ecamara           #+#    #+#              #
#    Updated: 2023/05/19 17:10:46 by ecamara          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang++
CPPFLAGS = -std=c++17 -Wall -Wextra -O2 -mavx -mavx2 -march=native -g3 -fsanitize=address 

SRC_FILES =	src/main.cpp\
			src/Client.cpp\
			src/Map.cpp\
			src/Data.cpp\
			src/RenderEngine.cpp

OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Libraries
INCLUDES = -I./libraries
LIBS = -L./../libraries/mlx -lmlx -framework OpenGL -framework AppKit
STATIC_LIB = ../libraries/UDP/UdpConnection.a
#LIBS = -L/usr/local/lib -L/Users/ecamara/.brew/lib -lglfw -lvulkan
#INCLUDES = -I/usr/local/include -I/Users/ecamara/.brew/include


NAME = client

all: $(NAME)


$(NAME): $(OBJ_FILES)
	$(MAKE) -C ../libraries/mlx
	$(CC) $(CPPFLAGS) $(LIBS) $(INCLUDES) $(STATIC_LIB) $^ -o $@

%.o: %.cpp
	$(CC) $(CPPFLAGS) $(LIBS) $(INCLUDES) -c $^ -o $@



clean:
	rm -f $(OBJ_FILES) $(NAME)

re: clean all

.PHONY: all clean re

