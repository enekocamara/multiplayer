# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 12:59:03 by ecamara           #+#    #+#              #
#    Updated: 2023/05/22 13:27:31 by ecamara          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang++
CPPFLAGS = -std=c++17 -Wall -Werror -Wextra -O2 -mavx -mavx2 -march=native -g# -g3 -fsanitize=address 

SRC_FILES =	src/main.cpp\
			src/Client.cpp\
			src/Map.cpp\
			src/Data.cpp\
			src/RenderEngine.cpp

OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Libraries
INCLUDES = -I./libraries
STATIC_MLX = ../libraries/mlx/libmlx.a #
STATIC_UDP = ../libraries/UDP/UdpConnection.a
MLX_FLAGS = -framework OpenGL -framework AppKit
#LIBS = -L/usr/local/lib -L/Users/ecamara/.brew/lib -lglfw -lvulkan
#INCLUDES = -I/usr/local/include -I/Users/ecamara/.brew/include


NAME = client

all: $(NAME)


$(NAME): $(OBJ_FILES) $(STATIC_UDP) $(STATIC_MLX)
	$(MAKE) -C ../libraries/mlx
	$(MAKE) -C ../libraries/UDP
	$(CC) $(CPPFLAGS) $(INCLUDES) $(STATIC_UDP) $(STATIC_MLX) $(MLX_FLAGS) $^ -o $@

%.o: %.cpp 
	$(CC) $(CPPFLAGS) $(INCLUDES) -c $^ -o $@



clean:
	rm -f $(OBJ_FILES) $(NAME)

re: clean all

.PHONY: all clean re

