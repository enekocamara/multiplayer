/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:29:25 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/16 16:01:23 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libraries/glm/glm.hpp"
#include "../../libraries/includes/header.h"
#include <iostream>
#include <vector>
#include <poll.h>
#include "User.hpp"

class Data{
	public:
		Data();
		~Data();
		pollfd		*pollData();
		User		*userData();
		Entity		*playersData();
		Entity		*entitiesData();
		
		uint32_t	playerSize() const;
		uint32_t	entitySize() const;
		
		User &operator[](userIt idx);
		const User &operator[](userIt idx) const;
		pollfd &operator[](pollfdIt idx);
		const pollfd &operator[](pollfdIt idx) const;
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

		void		addUser(int fd, std::string username  = "nobody");
		void		addEntity(Entity entity);
		pollfdIt p_begin();
		userIt u_begin();
	private:
		std::vector<pollfd> pollfdVector;
		std::vector<User> users;

		//std::vector<glm::vec2>positions;
		//std::vector<glm::vec2>velocities;
		//std::vector<uint32_t>id;
		//std::vector<uint32_t>flags;

		std::vector<Entity>players;
		std::vector<Entity>entities;
};