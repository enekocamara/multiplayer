/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:23:04 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/17 12:24:33 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Data.hpp"

Data::Data()
{

}

Data::~Data()
{
	
}

void	Data::updatePlayers(char *buffer, uint32_t size)
{
	if (size % sizeof(Entity) != 0) {
		std::cerr << "Invalid player buffer size\nsize: " << size <<" sizeOf: " << sizeof(Info) << "\n";
		//exit(0);
		return;
	}

	// Compute the number of elements to copy
	uint32_t num_elems = size / sizeof(Entity);
	
	// Resize the positions vector to hold the new data
	players.resize(num_elems);
	
	// Copy the data from buffer to positions
	memcpy(players.data(), buffer, size);
	
	// Free the buffer
	//delete[] buffer;
	
	// Print the first position for debugging
	std::cout << color::red << "recv pos [" << players[0].pos.x << ',' << players[0].pos.y << "]\n" << color::reset; 
}

void	Data::updateEntities(char *buffer, uint32_t size)
{
	if (size % sizeof(Entity) != 0) {
		std::cerr << "Invalid entities buffer size" << std::endl;
		return;
	}

	// Compute the number of elements to copy
	uint32_t num_elems = size / sizeof(Entity);
	
	// Resize the positions vector to hold the new data
	entities.resize(num_elems);
	
	// Copy the data from buffer to positions
	memcpy(entities.data(), buffer, size);
}

uint32_t Data::playersSize() const
{
	return players.size();
}

uint32_t Data::entitiesSize() const
{
	return entities.size();
}

glm::vec2 &Data::operator[](posIt idx)
{
	return players[idx].pos;
}

const glm::vec2 &Data::operator[](posIt idx) const
{
	return players[idx].pos;
}

glm::vec2 &Data::operator[](velIt idx)
{
	return players[idx].vel;
}

const glm::vec2 &Data::operator[](velIt idx) const
{
	return players[idx].vel;
}

uint32_t &Data::operator[](idIt idx)
{
	uint64_t& data64 = players[idx].data;
	uint32_t& data32 = reinterpret_cast<uint32_t&>(data64); // alias the data as a 32-bit integer
	return data32; // return the first 32 bits of the 64-bit integer
}

const uint32_t &Data::operator[](idIt idx) const
{
	const uint64_t& data64 = players[idx].data;
	const uint32_t& data32 = reinterpret_cast<const uint32_t&>(data64); // alias the data as a 32-bit integer
	return data32; // return the first 32 bits of the 64-bit integer
}

uint32_t &Data::operator[](flagsIt idx)
{
	uint64_t &data = players[idx].data;
	return reinterpret_cast<uint32_t*>(&data)[1];
}

const uint32_t &Data::operator[](flagsIt idx) const
{
	const uint64_t &data = players[idx].data;
	return reinterpret_cast<const uint32_t*>(&data)[1];
}

Entity &Data::operator[](entityIt idx)
{
	return entities[idx];
}

const Entity &Data::operator[](entityIt idx) const
{
	return entities[idx];
}