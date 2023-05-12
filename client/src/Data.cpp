/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:23:04 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/11 17:41:16 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Data.hpp"

Data::Data()
{

}

Data::~Data()
{
	
}

void	Data::update(char *buffer, uint32_t size)
{
	if (size % sizeof(glm::vec2) != 0) {
		std::cerr << "Invalid buffer size" << std::endl;
		return;
	}

	// Compute the number of elements to copy
	uint32_t num_elems = size / sizeof(glm::vec2);
	
	// Resize the positions vector to hold the new data
	positions.resize(num_elems);
	
	// Copy the data from buffer to positions
	memcpy(positions.data(), buffer, size);
	
	// Free the buffer
	//delete[] buffer;
	
	// Print the first position for debugging
	//std::cout << positions[0].x << "," << positions[0].y << '\n';
}

glm::vec2 &Data::operator[](uint32_t idx)
{
	return positions[idx];
}

uint32_t Data::size() const
{
	return positions.size();
}