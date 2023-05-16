/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:23:06 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/16 16:30:01 by ecamara          ###   ########.fr       */
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
		
		uint32_t	playersSize()const;
		uint32_t	entitiesSize()const;
		void		updatePlayers(char *buffer, uint32_t size);
		void		updateEntities(char *buffer, uint32_t size);
		void		addEntity(Entity entity);
		
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
		Entity &operator[](entityIt idx);
		const Entity &operator[](entityIt idx) const;
		
	private:
		//std::vector<glm::vec2>positions;
		//std::vector<uint32_t>id;
		//std::vector<uint32_t>flags;
		std::vector<Entity>players;
		std::vector<Entity>entities;
};