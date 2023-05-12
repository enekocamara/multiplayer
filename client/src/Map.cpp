/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:30:49 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/11 19:43:52 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Map.hpp"

Map::Map()
{
	
}

Map::Map(void *mlx, std::string mapPath): mlx(mlx)
{
	initTextureAtlas();
	readMap(mapPath);
}

Map::~Map()
{
	
}

void Map::readMap(std::string mapPath)
{
	std::ifstream file(mapPath.c_str());
	
	if (!file.is_open())
		throw std::runtime_error("failed to open [" + mapPath + "]file");

	std::string line;
	bool	first = true;
	height = 0;
	while (std::getline(file, line))
	{
		if (first)
		{
			width = line.size();
			first = false;
		}
		for(uint32_t i = 0; i < line.size(); i++)
		{
			if (line[i] != '\n')
				map.push_back(line[i] - 48);
		}
		height++;
	}
	file.close();
	//printMap();
	createMapImg();
}

void	Map::createMapImg()
{
	// Create a new image to hold the combined images
	bmlx_create_img(mlx, &mapImg, width * TILE, height * TILE);
	if (mapImg.img == NULL)
		std::cout << "ERROR MAP IMAGE NOT CREATED\n";

// Loop through each image and copy it into the combined image
	for (uint32_t y = 0; y < height; y++)
	{
		for (uint32_t x = 0; x < width; x++)
		{
			bmlx_put_img_to_img(&mapImg, &textureAtlas[map[y * width + x]], x * TILE + y * width * TILE * TILE, TILE, width * TILE);
		}
	}
}


void	Map::printMap()
{
	std::cout << "map size " << map.size() << " height " << height << " width " << width << '\n';
	for (uint32_t i = 0; i < map.size(); i++)
	{
		std::cout << map[i];
	}
}

void	Map::initTextureAtlas()
{
	t_image wall;
	t_image grass;
	t_image player;
	int sizeY = TILE;
	int sizeX = TILE;
	char *pathGrass = "textures/grass/tile000.xpm";
	char *pathWall = "textures/walls/all-4.xpm";
	char *playerPath = "textures/walls/all-0.xpm";
	bmlx_create_img_xpm(mlx, &grass, pathGrass, sizeX, sizeY);
	bmlx_create_img_xpm(mlx, &wall, pathWall, sizeX, sizeY);
	bmlx_create_img_xpm(mlx, &player, playerPath, sizeX, sizeY);
	if (grass.img == NULL || wall.img == NULL || player.img == NULL)
	{
		throw std::runtime_error("failed to create image");
	}
	textureAtlas.reserve(3);
	textureAtlas.push_back(grass);
	textureAtlas.push_back(wall);
	textureAtlas.push_back(player);
}

t_image Map::operator[](uint32_t mapPos)
{
	return textureAtlas[map[mapPos]];
}

t_image Map::getTexture(uint32_t idx)
{
	return textureAtlas[idx];
}