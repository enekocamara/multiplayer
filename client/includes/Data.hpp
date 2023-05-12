/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:23:06 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/12 16:02:38 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../../libraries/glm/glm.hpp"
#include "../../libraries/includes/header.h"
#include <vector>
#include <iostream>

class Data{
	public:
		Data();
		~Data();
		uint32_t	size()const;
		void	update(char *buffer, uint32_t size);
		glm::vec2 &operator[](uint32_t idx);
		glm::vec2	myPos{1.1f,-1.1};

		glm::vec2 &operator[](posIt idx);
		const glm::vec2 &operator[](posIt idx) const;
		glm::vec2 &operator[](velIt idx);
		const glm::vec2 &operator[](velIt idx) const;
		uint32_t &operator[](idIt idx);
		const uint32_t &operator[](idIt idx) const;
		uint32_t &operator[](flagsIt idx);
		const uint32_t &operator[](flagsIt idx) const;
		
	private:
		//std::vector<glm::vec2>positions;
		//std::vector<uint32_t>id;
		//std::vector<uint32_t>flags;
		std::vector<Entity>entities;
};