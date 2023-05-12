/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:31:18 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/12 13:49:21 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

extern "C" {
#include "../../libraries/mlx/betterMlx.h"
}

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#define TILE 32

class Map{
	public:
		Map();
		Map(void *mlx, std::string mapPath);
		~Map();

		t_image operator[](uint32_t mapPos);
		t_image getTexture(uint32_t idx);
		uint32_t	getValue(uint32_t mapPos) const;
		uint32_t	getHeight()const{return height;}
		uint32_t	getWidth() const{return width;}
		void		*getMap(){return mapImg.img;}
	private:
		void		readMap(std::string mapPath);
		void		initTextureAtlas();
		void		printMap();
		void		createMapImg();
		uint32_t	height;
		uint32_t	width;
		std::vector<uint32_t>map;
		std::vector<t_image>textureAtlas;
		t_image		mapImg;
		void		*mlx;
};